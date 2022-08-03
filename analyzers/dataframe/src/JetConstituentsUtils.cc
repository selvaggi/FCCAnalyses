#include "FCCAnalyses/JetConstituentsUtils.h"
#include "FCCAnalyses/ReconstructedParticle.h"


namespace FCCAnalyses {
  namespace JetConstituentsUtils {
    rv::RVec<FCCAnalysesJetConstituents> build_constituents(rv::RVec<edm4hep::ReconstructedParticleData> jets,
                                                            rv::RVec<edm4hep::ReconstructedParticleData> rps) {
      rv::RVec<FCCAnalysesJetConstituents> jcs;
      for (const auto& jet : jets) {
        auto& jc = jcs.emplace_back();
        for (auto it = jet.particles_begin; it < jet.particles_end; ++it)
          jc.emplace_back(rps.at(it));
      }
      return jcs;
    }

    FCCAnalysesJetConstituents get_jet_constituents(rv::RVec<FCCAnalysesJetConstituents> csts, int jet) {
      if (jet < 0)
        return FCCAnalysesJetConstituents();
      return csts.at(jet);
    }

    rv::RVec<FCCAnalysesJetConstituents> get_constituents(rv::RVec<FCCAnalysesJetConstituents> csts,
                                                          rv::RVec<int> jets) {
      rv::RVec<FCCAnalysesJetConstituents> jcs;
      for (size_t i = 0; i < jets.size(); ++i)
        if (jets.at(i) >= 0)
          jcs.emplace_back(csts.at(i));
      return jcs;
    }

    /// recasting helper for jet constituents methods
    /// \param[in] jcs collection of jets constituents
    /// \param[in] meth variables retrieval method for constituents
    auto cast_constituent = [](const auto& jcs, auto&& meth) {
      rv::RVec<FCCAnalysesJetConstituentsData> out;
      for (const auto& jc : jcs)
        out.emplace_back(meth(jc));
      return out;
    };

    auto cast_constituent_2 = [](const auto& jcs, const auto& coll, auto&& meth) {
    //auto cast_constituent_2 = [](const auto& jcs, auto&& meth) {
      rv::RVec<FCCAnalysesJetConstituentsData> out;
      for (const auto& jc : jcs) {
        //std::cout<<"new jet:  " <<jc.size()<<std::endl;
        out.emplace_back(meth(jc, coll));
        //out.emplace_back(meth(jc));
      }
      return out;
    };
    
    rv::RVec<FCCAnalysesJetConstituentsData> get_pt(rv::RVec<FCCAnalysesJetConstituents> jcs) {
      return cast_constituent(jcs, ReconstructedParticle::get_pt);
    }

    rv::RVec<FCCAnalysesJetConstituentsData> get_e(rv::RVec<FCCAnalysesJetConstituents> jcs) {
      return cast_constituent(jcs, ReconstructedParticle::get_e);
    }

    rv::RVec<FCCAnalysesJetConstituentsData> get_theta(rv::RVec<FCCAnalysesJetConstituents> jcs) {
      return cast_constituent(jcs, ReconstructedParticle::get_theta);
    }

    rv::RVec<FCCAnalysesJetConstituentsData> get_phi(rv::RVec<FCCAnalysesJetConstituents> jcs) {
      return cast_constituent(jcs, ReconstructedParticle::get_phi);
    }

    rv::RVec<FCCAnalysesJetConstituentsData> get_type(rv::RVec<FCCAnalysesJetConstituents> jcs) {
      return cast_constituent(jcs, ReconstructedParticle::get_type);
    }

    rv::RVec<FCCAnalysesJetConstituentsData> get_charge(rv::RVec<FCCAnalysesJetConstituents> jcs) {
      return cast_constituent(jcs, ReconstructedParticle::get_charge);
    }

    /*
    rv::RVec<FCCAnalysesJetConstituentsData> get_dptdpt(const rv::RVec<FCCAnalysesJetConstituents> jcs, ROOT::VecOps::RVec<edm4hep::TrackState> tracks ) {
    //rv::RVec<FCCAnalysesJetConstituentsData> get_dptdpt(const rv::RVec<FCCAnalysesJetConstituents> jcs) {
      //std::cout<<"pt size:  " << cast_constituent_2(jcs, tracks, ReconstructedParticle2Track::getRP2TRK_z0_tanlambda_cov).size() <<std::endl;
      std::cout<<"jet size:  " << cast_constituent(jcs, ReconstructedParticle::get_charge).size() << ", " <<std::endl;
      return cast_constituent_2(jcs, tracks, ReconstructedParticle2Track::getRP2TRK_z0_tanlambda_cov);
      //return cast_constituent_2(jcs, ReconstructedParticle2Track::getRP2TRK_z0_tanlambda_cov);
    }
    */

    rv::RVec<FCCAnalysesJetConstituentsData> get_erel_log(rv::RVec<edm4hep::ReconstructedParticleData>& jets, rv::RVec<FCCAnalysesJetConstituents>& jcs) {
      rv::RVec<FCCAnalysesJetConstituentsData> out;
      for (size_t i = 0; i < jets.size(); ++i) {
        auto& jet_csts = out.emplace_back();
        float e_jet = jets.at(i).energy;
        auto csts = get_jet_constituents(jcs, i);
        for (const auto& jc : csts) {
          float val = (e_jet > 0.) ? jc.energy/e_jet : 1.;
          float erel_log = float(std::log10(val));
          jet_csts.emplace_back(erel_log);
        }
      }
      return out;
    }

    rv::RVec<FCCAnalysesJetConstituentsData> get_thetarel(const rv::RVec<edm4hep::ReconstructedParticleData>& jets, const rv::RVec<FCCAnalysesJetConstituents>& jcs) {
      rv::RVec<FCCAnalysesJetConstituentsData> out;
      for (size_t i = 0; i < jets.size(); ++i) {
        auto& jet_csts = out.emplace_back();
        TLorentzVector tlv_jet;
        tlv_jet.SetXYZM(jets.at(i).momentum.x, jets.at(i).momentum.y, jets.at(i).momentum.z, jets.at(i).mass);
        float theta_jet = tlv_jet.Theta();
        float phi_jet = tlv_jet.Phi();
        auto csts = get_jet_constituents(jcs, i);
          for (const auto& jc : csts) {
            TLorentzVector tlv_const;
            tlv_const.SetXYZM(jc.momentum.x, jc.momentum.y, jc.momentum.z, jc.mass);
            TVector3 v_const = tlv_const.Vect();
            v_const.RotateZ(-phi_jet);
            v_const.RotateY(-theta_jet);
            float theta_rel = v_const.Theta();
            jet_csts.emplace_back(theta_rel);
        }
      }
      return out;
    }


    rv::RVec<FCCAnalysesJetConstituentsData> get_phirel(const rv::RVec<edm4hep::ReconstructedParticleData>& jets, const rv::RVec<FCCAnalysesJetConstituents>& jcs) {
      rv::RVec<FCCAnalysesJetConstituentsData> out;
      for (size_t i = 0; i < jets.size(); ++i) {
        auto& jet_csts = out.emplace_back();
        TLorentzVector tlv_jet;
        tlv_jet.SetXYZM(jets.at(i).momentum.x, jets.at(i).momentum.y, jets.at(i).momentum.z, jets.at(i).mass);
        float theta_jet = tlv_jet.Theta();
        float phi_jet = tlv_jet.Phi();
        auto csts = get_jet_constituents(jcs, i);
          for (const auto& jc : csts) {
            TLorentzVector tlv_const;
            tlv_const.SetXYZM(jc.momentum.x, jc.momentum.y, jc.momentum.z, jc.mass);
            TVector3 v_const = tlv_const.Vect();
            v_const.RotateZ(-phi_jet);
            v_const.RotateY(-theta_jet);
            float phi_rel = v_const.Phi();
            jet_csts.emplace_back(phi_rel);
        }
      }
      return out;
    }

  }  // namespace JetConstituentsUtils
}  // namespace FCCAnalyses
