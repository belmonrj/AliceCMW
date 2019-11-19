void runGrid()
{

  gSystem->Load("libCore.so");  
  gSystem->Load("libTree.so");
  gSystem->Load("libGeom.so");
  gSystem->Load("libVMC.so");
  gSystem->Load("libPhysics.so");
  gSystem->Load("libSTEERBase");
  gSystem->Load("libESD");
  gSystem->Load("libAOD");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");   
  gROOT->ProcessLine(".include $ROOTSYS/include");
  gROOT->ProcessLine(".include $ALICE_ROOT/include");



  gROOT->LoadMacro("CreateAlienHandler.C");
  AliAnalysisGrid *alienH = CreateAlienHandler();  
  if(!alienH) return;
  AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskCMEv2A");
  mgr->SetGridHandler(alienH);
  AliAODInputHandler *aodH = new AliAODInputHandler();
  mgr->SetInputEventHandler(aodH);

  gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
  AddTaskPIDResponse(kTRUE); // simulation data?? worked for LHC11a10a
  //AddTaskPIDResponse(0); // real data, also worked fine for LHC13d2 sim data



  cout<<"Memory address of AliAnalysisManager is "<<mgr<<endl;

  gROOT->LoadMacro("AliAnalysisTaskCMEv2A.cxx++g");   



  // ------------------------------------ //
  // --- AddTask should start here... --- //
  // ------------------------------------ //

  // AliAnalysisTask *task = new AliAnalysisTaskCMEv2A("TaskCMEv2A");
  // mgr->AddTask(task);
  // AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();
  // AliAnalysisDataContainer *coutput = mgr->CreateContainer("chist",
  // 							   TList::Class(),
  // 							   AliAnalysisManager::kOutputContainer,
  // 							   "test.root");
  // mgr->ConnectInput(task,0,cinput);
  // mgr->ConnectOutput(task,1,coutput);

  // --- these line replaces the preceding lines ------------------------------------
  gROOT->LoadMacro("AddTaskCMEv2A.C");
  // --- MUST call AddTask to process
  AliAnalysisTaskCMEv2A *ptr = AddTaskCMEv2A();
  if(ptr) cout<<"Success!  AddTask = "<<ptr<<endl;
  else cout<<"Failure!  Could not add task, prepare for ultimate suffering..."<<endl;
  // --------------------------------------------------------------------------------

  // ---------------------------------- //
  // --- AddTask should end here... --- //
  // ---------------------------------- //


  int debug = ptr->GetDebug();
  mgr->SetDebugLevel(debug);
  if(!mgr->InitAnalysis()) return;
  mgr->PrintStatus();
  mgr->StartAnalysis("grid");

}
