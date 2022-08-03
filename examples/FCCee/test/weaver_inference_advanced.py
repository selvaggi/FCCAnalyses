
#Mandatory: List of processes
processList = {
    #'p8_ee_ZH_ecm240':{'fraction':0.2, 'chunks':2, 'output':'p8_ee_ZH_ecm240_out'}
    'p8_noBES_ee_H_Hbb_ecm125':{'fraction':0.01, 'chunks':1, 'output':'test_out'}
}

#Mandatory: Production tag when running over EDM4Hep centrally produced events, this points to the yaml files for getting sample statistics
prodTag     = "FCCee/spring2021/IDEA/"

#Optional: output directory, default is local running directory
outputDir   = "."

#Optional
nCPUS       = 8
runBatch    = False
#batchQueue = "longlunch"
#compGroup = "group_u_FCC.local_gen"

#Mandatory: RDFanalysis class where the use defines the operations on the TTree
class RDFanalysis():
    #__________________________________________________________
    #Mandatory: analysers funtion to define the analysers to process, please make sure you return the last dataframe, in this example it is df2
    def analysers(df):
        from ROOT import JetFlavourUtils

        weaver = JetFlavourUtils.setup_weaver(
            "/afs/cern.ch/user/s/selvaggi/public/weaver/models/h_fccee_flavtagging_paper_v8.onnx",
            "/afs/cern.ch/user/s/selvaggi/public/weaver/models/preprocess_h_fccee_flavtagging_paper_v8.json",
            (
                "pfcand_erel_log",
                "pfcand_thetarel",
                "pfcand_phirel",
                "pfcand_dptdpt",
                "pfcand_detadeta",
                "pfcand_dphidphi",
                "pfcand_dxydxy",
                "pfcand_dzdz",
                "pfcand_dxydz",
                "pfcand_dphidxy",
                "pfcand_dlambdadz",
                "pfcand_dxyc",
                "pfcand_dxyctgtheta",
                "pfcand_phic",
                "pfcand_phidz",
                "pfcand_phictgtheta",
                "pfcand_cdz",
                "pfcand_cctgtheta",
                "pfcand_mtof",
                "pfcand_mtofn",
                "pfcand_dndx",
                "pfcand_charge",
                "pfcand_isMu",
                "pfcand_isEl",
                "pfcand_isChargedHad",
                "pfcand_isGamma",
                "pfcand_isNeutralHad",
                "pfcand_dxy",
                "pfcand_dz",
                "pfcand_btagSip2dVal",
                "pfcand_btagSip2dSig",
                "pfcand_btagSip3dVal",
                "pfcand_btagSip3dSig",
                "pfcand_btagJetDistVal",
                "pfcand_btagJetDistSig",
            ),
        )


        df2 = (
            df
            # retrieve all information about jet constituents for each jet in collection
            # .Define("JetsConstituents", "JetConstituentsUtils::build_constituents(Jet, ReconstructedParticles)")
            .Define(
                "JetsConstituents",
                "JetConstituentsUtils::build_constituents(Jet, ReconstructedParticles)",
            )
            .Define("JC_erel_log", "JetConstituentsUtils::get_erel_log(Jet, JetsConstituents)")
            .Define("JC_thetarel", "JetConstituentsUtils::get_thetarel(Jet, JetsConstituents)")
            .Define("JC_phirel", "JetConstituentsUtils::get_phirel(Jet, JetsConstituents)")
            #.Define("JC_dptdpt", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dptdpt", "JetConstituentsUtils::get_dptdpt(JetsConstituents, EFlowTrack_1)")
            .Define("JC_detadeta", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dphidphi", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dxydxy", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dzdz", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dxydz", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dphidxy", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dlambdadz", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dxyc", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dxyctgtheta", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_phic", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_phidz", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_phictgtheta", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_cdz", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_cctgtheta", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_mtof", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_mtofn", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dndx", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_charge", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_isMu", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_isEl", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_isChargedHad", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_isGamma", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_isNeutralHad", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dxy", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_dz", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_btagSip2dVal", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_btagSip2dSig", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_btagSip3dVal", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_btagSip3dSig", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_btagJetDistVal", "JetConstituentsUtils::get_e(JetsConstituents)")
            .Define("JC_btagJetDistSig", "JetConstituentsUtils::get_e(JetsConstituents)")
            # run inference
            .Define(
                "MVAVec",
                "JetFlavourUtils::get_weights(\
                    JC_erel_log,\
            	    JC_thetarel,\
                    JC_phirel,\
                    JC_dptdpt,\
                    JC_detadeta,\
                    JC_dphidphi,\
                    JC_dxydxy,\
                    JC_dzdz,\
                    JC_dxydz,\
                    JC_dphidxy,\
                    JC_dlambdadz,\
                    JC_dxyc,\
                    JC_dxyctgtheta,\
                    JC_phic,\
                    JC_phidz,\
                    JC_phictgtheta,\
                    JC_cdz,\
                    JC_cctgtheta,\
                    JC_mtof,\
                    JC_mtofn,\
                    JC_dndx,\
                    JC_charge,\
                    JC_isMu,\
                    JC_isEl,\
                    JC_isChargedHad,\
                    JC_isGamma,\
                    JC_isNeutralHad,\
                    JC_dxy,\
                    JC_dz,\
                    JC_btagSip2dVal,\
                    JC_btagSip2dSig,\
                    JC_btagSip3dVal,\
                    JC_btagSip3dSig,\
                    JC_btagJetDistVal,\
                    JC_btagJetDistSig\
                )",
            )              
         
            # recast output
            .Define("Jet_isG", "JetFlavourUtils::get_weight(MVAVec, 0)")
            .Define("Jet_isQ", "JetFlavourUtils::get_weight(MVAVec, 1)")
            .Define("Jet_isS", "JetFlavourUtils::get_weight(MVAVec, 2)")
            .Define("Jet_isC", "JetFlavourUtils::get_weight(MVAVec, 3)")
            .Define("Jet_isB", "JetFlavourUtils::get_weight(MVAVec, 4)")
        )

        return df2

    #__________________________________________________________
    #Mandatory: output function, please make sure you return the branchlist as a python list
    def output():
        branchList = [
                'Jet_isG', 'Jet_isQ', 'Jet_isS', 'Jet_isC', 'Jet_isB',
                ]
        return branchList
