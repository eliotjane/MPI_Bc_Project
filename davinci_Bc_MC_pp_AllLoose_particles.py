#adapted from Starterkit second lessons 02.optimized.py
from Configurables import DaVinci
from GaudiConf import IOHelper

# Load algorithms
from Configurables import CombineParticles
from Configurables import DecayTreeTuple, TupleToolTISTOS, TupleToolRecoStats, TupleToolPropertime
from DecayTreeTuple.Configuration import *

# Load input particles
from StandardParticles import StdAllNoPIDsPions as Pions
from StandardParticles import StdAllLooseMuons as Muons

#stripping documentation
#http://lhcbdoc.web.cern.ch/lhcbdoc/stripping/config/stripping34/commonparticles/stdallloosepions.html

# Load Selection objects
from PhysConf.Selections import CombineSelection, Combine3BodySelection, FilterSelection, StrippingSelection, AutomaticData, TupleSelection
from PhysConf.Selections import SelectionSequence

#for stripping emulation
from StandardParticles import StdLooseJpsi2MuMu as LooseJpsi

#Input into LooseJpsi is StdAllNoPIDsPions with 	(ADAMASS('J/psi(1S)') < 100.*MeV) & (ADOCACHI2CUT(30,'')) as mass cuts.


#select the pp dimu stripping line
#stream = 'IFT'
#stream = 'AllStreams'
#line = 'HeavyIonDiMuonJpsi2MuMuLine'
#line = 'FullDSTDiMuonJpsi2MuMuTOSLine'
#line = 'FullDSTDiMuonJpsi2MuMuDetachedLine'
#strip_input = AutomaticData('/Event/Dimuon/Phys/{0}/Particles'.format(line))
#strip_input = AutomaticData('/Event/AllStreams/Phys/{0}/Particles'.format(line))

#Select the muons for the Jpsi; there's a PID cut in here
strip_input = FilterSelection(
'strip_sel',
[LooseJpsi],
Code="(((BPVDLS>3) | (BPVDLS<-3))) & (MINTREE('mu+'==ABSID,PIDmu) > 0.0) & ((MM > 2996.916) & (MM < 3196.916)) & (VFASPF(VCHI2PDOF)< 20.0) & (MINTREE('mu+'==ABSID,PT) > 500.0 *MeV)"
)

#create the J/psi
Jpsi_sel = FilterSelection(
    'Sel_Jpsi',
    [strip_input],
    Code="(ADMASS('J/psi(1S)') < 50*MeV) & (PT > 500*MeV)"
)

#Select pions: there's no PID cut here
Pion_sel = FilterSelection(
    'Sel_Pions',
    [Pions],
    Code='(TRCHI2DOF < 3) & (PT > 1000*MeV) & (P > 3000*MeV)'
)


#B_comb = ' (ADOCA(1,3)<0.5*mm) & (ADOCA(2,3)<0.5*mm) '

#combint the two particles
B_comb = '(ADOCA(1,2)<0.5*mm)'

#select the B+ and Bc+ mass range
B_mother =  'in_range(5.0 * GeV ,  M , 6.5 * GeV) & (VFASPF(VCHI2/VDOF)<5)'
#B_mother =  'in_range(6.0 * GeV ,  M , 6.5 * GeV) & (VFASPF(VCHI2/VDOF)<10)'

#Combine Jpsi and pion into B_c
B_sel = CombineSelection(
        'B_sel',
            [Jpsi_sel, Pion_sel],
        #    DecayDescriptor='[psi(2S) -> J/psi(1S) pi+ pi-]cc',
            DecayDescriptor='[B+ -> J/psi(1S) pi+]cc',
            CombinationCut=B_comb,
            MotherCut=B_mother,
        )


B_seq = SelectionSequence('B_Seq', TopSelection=B_sel)

dtt = DecayTreeTuple('Btuple')
dtt.Inputs = B_seq.outputLocations()
#dtt.Decay = '[psi(2S) -> ^(J/psi(1S) -> ^mu+ ^mu-) ^pi+ ^pi-]CC'
#dtt.setDescriptorTemplate('${psi2s}[psi(2S) -> ${Jpsi}(J/psi(1S) -> ${mum}mu- ${mup}mu+) ${pip}pi+ ${pim}pi-]CC')#better way insted of defining each individually
#dtt.setDescriptorTemplate('${psi2s}(psi(2S) -> ${Jpsi}(J/psi(1S) -> ${mum}mu- ${mup}mu+) ${pip}pi+ ${pim}pi-)')
dtt.setDescriptorTemplate('${B}[B+ -> ${Jpsi}(J/psi(1S) -> ${mum}mu- ${mup}mu+) ${pi}pi+]CC')

ttreco = dtt.addTupleTool('TupleToolRecoStats')
ttprimaries = dtt.addTupleTool('TupleToolPrimaries')
ttproptime = dtt.B.addTupleTool('TupleToolPropertime')

#Check if DLS can be found
#ttreco.Verbose = True
#ttprimaries.Verbose = True
#ttproptime.Verbose = True

#Commented out for LDST run

#add modifications from correspondance with Tom.
mcpvtom = dtt.B.addTupleTool('TupleToolPVTrackInfo')
#unnecssary given we set the location in the tool
#mcpvtom.PVsLocation    = 'Rec/Vertex/Primary'
mcpvtom.RefitPVs = True
mcpvtom.TruthMatchPVs = False
#mcpvtom.TruthMatchPVs = True
#dtt.B.addTupleTool('TupleToolPVTrackInfo')



track_tool = dtt.addTupleTool('TupleToolTrackInfo')
track_tool.Verbose = True

#Add event info
etuple=EventTuple()
etuple.ToolList=["TupleToolEventInfo"]

#Add TISTOS info
tistos = dtt.B.addTupleTool(TupleToolTISTOS, name="TupleToolTISTOS")
tistos.VerboseL0=True
tistos.VerboseHlt1=True
tistos.VerboseHlt2=True
tistos.TriggerList=["L0MuonDecision", "Hlt1DiMuonHighMassDecision"]

tistos2 = dtt.Jpsi.addTupleTool(TupleToolTISTOS, name="TupleToolTISTOS")
tistos2.VerboseL0=True
tistos2.VerboseHlt1=True
tistos2.VerboseHlt2=True
tistos2.TriggerList=["L0MuonDecision","L0DiMuonDecision","Hlt1DiMuonHighMassDecision","Hlt2DiMuonDetachedJPsiDecision"]

#Add DecayTreeFitter
dtt.B.addTupleTool('TupleToolDecayTreeFitter/DTF_ConsJpsi')#DTF_ConsJspi is the name we give it, since it is used to constrain Jpsi
dtt.B.DTF_ConsJpsi.constrainToOriginVertex = False
dtt.B.DTF_ConsJpsi.Verbose = True
#dtt.B.DTF_ConsJpsi.daughtersToConstrain = ['J/psi(1S)'] #this one takes a list
#dtt.B.DTF_ConsJpsi.UpdateDaughters = True

#add MC truth information
#mctruth = dtt.B.addTupleTool('TupleToolMCTruth/mctruth')
#mctruth.ToolList = ["MCTupleToolKinematic","MCTupleToolHierarchy"]

#Truth matching algorithms from Tom Hadavizadeh (25/11/2022)

#from Configurables import TrackAssociator
#velotrassoc = TrackAssociator()
#velotrassoc.TracksInContainer = 'Rec/Track/FittedHLT1VeloTracks'

#from Configurables import LoKi__Track2MC
#lokitrassoc = LoKi__Track2MC()
#lokitrassoc.Tracks = ['Rec/Track/FittedHLT1VeloTracks']

#from Configurables import LoKi__PV2MC
#pv2mc = LoKi__PV2MC()
#pv2mc.MCVertices = 'MC/Vertices'
#pv2mc.Primaries =  'Rec/Vertex/Primary'

#new algorithms
#DaVinci().UserAlgorithms += [B_seq.sequence(),velotrassoc,lokitrassoc,  dtt, etuple]

#old algorithms
DaVinci().UserAlgorithms += [B_seq.sequence(), dtt, etuple]

# DaVinci configuration
DaVinci().InputType = 'DST'
DaVinci().TupleFile = 'Btuple_Selection.root'
#DaVinci().PrintFreq = 1000
#DaVinci().DataType = '2018'
#DaVinci().Simulation = False
DaVinci().Simulation = True
# Only ask for luminosity information when not using simulated data
DaVinci().Lumi = not DaVinci().Simulation
DaVinci().EvtMax = -1

#LDST Files
DaVinci().DataType = '2018'
#DaVinci().CondDBtag = 'sim-20190430-vc-md100'


#DST
DaVinci().CondDBtag = 'sim-20160614-1-vc-md100'
DaVinci().DDDBtag = 'dddb-20170721-3'

#DaVinci().DataType = '2012'
#DaVinci().CondDBtag = 'sim-20160321-2-vc-md100'
#DaVinci().DDDBtag = 'dddb-20170721-2'

#commeted out EJW
#DaVinci().CondDBtag = 'sim-20190430-vc-mu100' #get from header of .py file with LFNs downloaded from bookkeeping

#for simulation
#DaVinci().DDDBtag = 'dddb-20170721-3' #very important for simulations, this is detector configuration

#added for local testing
#from Configurables import CondDB
#CondDB(LatestGlobalTagByDataType='2018')#Use the local input data

#IOHelper().inputFiles([
#'root://xrootd.echo.stfc.ac.uk/lhcb:prod/lhcb/MC/2018/ALLSTREAMS.DST/00123502/0000/00123502_00000001_7.AllStreams.dst'
#], clear=True)

#'LFN:/MC/2011/Beam3500GeV-2011-MagDown-Nu2-BcVegPyPythia8/Sim09l/Trig0x40760037/Reco14c/Stripping21r1NoPrescalingFlagged/14143013/ALLSTREAMS.DST'
#'LFN:/lhcb/MC/2018/ALLSTREAMS.DST/00123502/0000/00123502_00000001_7.AllStreams.dst',
#'LFN:/lhcb/MC/2018/Beam6500GeV-2018-MagUp-Nu1.6-25ns-BcVegPyPythia8/Sim09j/Trig0x617d18a4/Reco18/Turbo05-WithTurcal/Stripping34NoPrescalingFlagged/14143013/ALLSTREAMS.DST',
#     'root://x509up_u140663@lhcbxrootd-kit.gridka.de//pnfs/gridka.de/lhcb/LHCb-Disk/lhcb/LHCb/Collision18/DIMUON.DST/00077434/0000/00077434_00001529_1.dimuon.dst',
#], clear=True)
#DaVinci().EvtMax = 2000

#IOHelper().inputFiles([('./00075559_00039636_1.dimuon.dst')],
#                      clear=True)
#IOHelper().inputFiles([('./00076144_00000002_1.ift.dst')], #IFT stripped pPb data
#                                            clear=True)

#IOHelper().inputFiles([('../00041836_00000021_1.dimuon.dst')], #8 TeV stripped pp dimuon data
#                                                                  clear=True)
