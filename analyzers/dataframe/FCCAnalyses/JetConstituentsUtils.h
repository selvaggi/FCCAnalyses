#ifndef FCCAnalyses_JetConstituentsUtils_h
#define FCCAnalyses_JetConstituentsUtils_h

#include "ROOT/RVec.hxx"
#include "edm4hep/ReconstructedParticle.h"
#include "FCCAnalyses/ReconstructedParticle2Track.h"

namespace FCCAnalyses {
  namespace JetConstituentsUtils {
    namespace rv = ROOT::VecOps;
    using FCCAnalysesJetConstituents = rv::RVec<edm4hep::ReconstructedParticleData>;
    using FCCAnalysesJetConstituentsData = rv::RVec<float>;

    rv::RVec<FCCAnalysesJetConstituents> build_constituents(rv::RVec<edm4hep::ReconstructedParticleData>,
                                                            rv::RVec<edm4hep::ReconstructedParticleData>);

    FCCAnalysesJetConstituents get_jet_constituents(rv::RVec<FCCAnalysesJetConstituents>, int);
    rv::RVec<FCCAnalysesJetConstituents> get_constituents(rv::RVec<FCCAnalysesJetConstituents>, rv::RVec<int>);

    rv::RVec<FCCAnalysesJetConstituentsData> get_pt(rv::RVec<FCCAnalysesJetConstituents>);
    rv::RVec<FCCAnalysesJetConstituentsData> get_e(rv::RVec<FCCAnalysesJetConstituents>);
    rv::RVec<FCCAnalysesJetConstituentsData> get_theta(rv::RVec<FCCAnalysesJetConstituents>);
    rv::RVec<FCCAnalysesJetConstituentsData> get_phi(rv::RVec<FCCAnalysesJetConstituents>);
    rv::RVec<FCCAnalysesJetConstituentsData> get_type(rv::RVec<FCCAnalysesJetConstituents>);
    rv::RVec<FCCAnalysesJetConstituentsData> get_charge(rv::RVec<FCCAnalysesJetConstituents>);
    
    rv::RVec<FCCAnalysesJetConstituentsData> get_dptdpt(const rv::RVec<FCCAnalysesJetConstituents>, const ROOT::VecOps::RVec<edm4hep::TrackState>);
    //rv::RVec<FCCAnalysesJetConstituentsData> get_dptdpt(const rv::RVec<FCCAnalysesJetConstituents>);

    rv::RVec<FCCAnalysesJetConstituentsData> get_erel_log(rv::RVec<edm4hep::ReconstructedParticleData>& jets, rv::RVec<FCCAnalysesJetConstituents>& jcs);
    rv::RVec<FCCAnalysesJetConstituentsData> get_thetarel(const rv::RVec<edm4hep::ReconstructedParticleData>& jets, const rv::RVec<FCCAnalysesJetConstituents>& jcs);
    rv::RVec<FCCAnalysesJetConstituentsData> get_phirel(const rv::RVec<edm4hep::ReconstructedParticleData>& jets, const rv::RVec<FCCAnalysesJetConstituents>& jcs);
  }  // namespace JetConstituentsUtils
}  // namespace FCCAnalyses

#endif
