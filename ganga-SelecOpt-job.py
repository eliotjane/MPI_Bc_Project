j = Job(name='Selection Opt data')
myApp = GaudiExec()
myApp.directory = "/afs/cern.ch/work/m/mwalton/stack/TupleScripts/DaVinciDev_v46r2"
j.application = myApp

#change "MC" to "data" for data submission
j.application.options = ['davinci_Bc_forSelecOpt.py']

j.application.platform = 'x86_64_v2-centos7-gcc11-opt'

#for real data
bkPath = '/LHCb/Collision18/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco18/Stripping34/90000000/DIMUON.DST'

#for simulation (DST)
#bkPath = '/MC/2018/Beam6500GeV-2018-MagUp-Nu1.6-25ns-BcVegPyPythia8/Sim09j/Trig0x617d18a4/Reco18/Turbo05-WithTurcal/Stripping34NoPrescalingFlagged/14143013/ALLSTREAMS.DST'

#for simulation (LDST)
#bkPath ='/MC/2018/Beam6500GeV-2018-MagDown-Nu1.6-25ns-BcVegPyPythia8/Sim09l/Trig0x617d18a4/Reco18/Turbo05-WithTurcal/Stripping34NoPrescalingFlagged/14143013/ALLSTREAMS.LDST'

data  = BKQuery(bkPath, dqflag=['OK']).getDataset()

##for testing purposes
j.inputdata = data[0:2]

#running on the full data
#j.inputdata = data[0:64]

#full data
#j.inputdata = data

j.backend = Dirac()
j.splitter = SplitByFiles(filesPerJob=1)

#Dirac Output
#j.outputfiles = [DiracFile('*.root')]

#local output
j.outputfiles = [LocalFile('*.root')]

#The MC LDST Job

j2 = Job(name='Selection Opt MC')
j2.application = myApp

#set the LDST options file 
j2.application.options = ['davinci_Bc_MC_forSelecOpt.py']

j2.application.platform = 'x86_64_v2-centos7-gcc11-opt'

#for simulation (DST)
#bkPath = '/MC/2018/Beam6500GeV-2018-MagUp-Nu1.6-25ns-BcVegPyPythia8/Sim09j/Trig0x617d18a4/Reco18/Turbo05-WithTurcal/Stripping34NoPrescalingFlagged/14143013/ALLSTREAMS.DST'

#for simulation (LDST)
bkPath_MC ='/MC/2018/Beam6500GeV-2018-MagDown-Nu1.6-25ns-BcVegPyPythia8/Sim09l/Trig0x617d18a4/Reco18/Turbo05-WithTurcal/Stripping34NoPrescalingFlagged/14143013/ALLSTREAMS.LDST'

data_MC  = BKQuery(bkPath_MC, dqflag=['OK']).getDataset()

##for testing purposes
j2.inputdata = data_MC[0:2]

#full data
#j.inputdata = data

j2.backend = Dirac()
j2.splitter = SplitByFiles(filesPerJob=1)

#Dirac Output
#j2.outputfiles = [DiracFile('*.root')]

#local output
j2.outputfiles = [LocalFile('*.root')]

j.submit()
j2.submit()
