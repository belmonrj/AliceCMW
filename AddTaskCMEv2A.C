AliAnalysisTaskCMEv2A *AddTaskCMEv2A
(
 int debug = 3,
 bool doMC = false,
 ULong64_t trigger = AliVEvent::kMB|AliVEvent::kCentral|AliVEvent::kSemiCentral,
 //ULong64_t trigger = AliVEvent::kMB|AliVEvent::kSemiCentral,
 //ULong64_t trigger = AliVEvent::kMB,
 bool dopupcut = true,
 bool doeffcorr = true,
 int centhandle = 1,
 //int centhandle = 2,
 //int fbit = 768,
 //int fbit = 128,
 int fbit = 1,
 float zvtxcut = 10.0,
 float centcut = 5.0,
 int nclscut = 60,
 float dcacutz = 50.0,
 float dcacutxy = 50.0,
 bool dodcacuts = false,
 float outeta = 0.8,
 float ineta = 0.5,
 float excleta = 0.0,
 float ptmin = 0.2,
 float ptmax = 5.0,
 bool doacuts = true,
 float nspid = 2.0,
 int cbinlo = 3,
 int cbinhi = 4,
 //bool donested = true,
 bool donested = false,
 bool dofoundcut = false,
 float centlo = 20.0,
 float centhi = 60.0,
 // float centlo = 20.0,
 // float centhi = 80.0,
 //float centlo = 0.0,
 //float centhi = 5.0,
 //float centlo = 70.0,
 //float centhi = 80.0,
 char *name = "TaskCMEv2A"
)
{

  if(doMC) trigger |= 1; // new

  // --- get analysis manager
  AliAnalysisManager *aam = AliAnalysisManager::GetAnalysisManager();
  if(!aam) 
    {
      cout<<"No analysis manager, now dying..."<<endl;
      return NULL;
    }  
  cout<<"Memory address of AliAnalysisManager is "<<aam<<endl;


  // --- check that input handler exists
  if(!aam->GetInputEventHandler())
    {
      cout<<"No input even handler, now dying..."<<endl;
      return NULL;
    }   


  // --- instantiate analysis task
  AliAnalysisTaskCMEv2A *task = new AliAnalysisTaskCMEv2A(name);
  cout<<"Memory address of task is "<<task<<endl;
  // --- set parameters
  task->SetParameters();
  // --- set task methods as needed
  task->SetDebug(debug);
  task->SetDoMC(doMC);
  task->SetTrigger(trigger);
  task->SetDoEffCorrection(doeffcorr);
  task->SetCentHandle(centhandle);
  task->SetFilterBit(fbit);
  task->SetZvtxCut(zvtxcut);
  task->SetCentCut(centcut);
  task->SetNclsCut(nclscut);
  task->SetDCAcutZ(dcacutz);
  task->SetDCAcutXY(dcacutxy);
  task->SetDoDCAcuts(dodcacuts);
  task->SetOutEta(outeta);
  task->SetInEta(ineta);
  task->SetExclEta(excleta);
  task->SetPtMin(ptmin);
  task->SetPtMax(ptmax);
  task->SetDoAcuts(doacuts);
  task->SetSigmaPID(nspid);
  task->SetCentBinLow(cbinlo);
  task->SetCentBinHigh(cbinhi);
  task->SetDoNested(donested);
  //task->SetDoFoundCut(dofoundcut);
  task->SetCentDCLow(centlo);
  task->SetCentDCHigh(centhi);


  // --- get input and output managers
  AliAnalysisDataContainer *aadci = aam->GetCommonInputContainer();
  AliAnalysisDataContainer *aadco = aam->CreateContainer
    (
     Form("List%s",name), 
     TList::Class(),    
     AliAnalysisManager::kOutputContainer, 
     //Form("Out%s_%s",name,AliAnalysisManager::GetCommonFileName())
     Form("Out%s.root",name)
     );
  // observe that ".root" is automatically appended


  // --- add task and connect input and output managers
  aam->AddTask(task);
  aam->ConnectInput(task,0,aadci);
  aam->ConnectOutput(task,1,aadco);

  // --- return pointer to Task
  return task;

}
