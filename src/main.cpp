#include <iostream>
#include <thread>
#include <chrono>

#include "../include/SettingSingleton.hpp"
#include "../include/Controller3D.hpp"
#include "../include/DataManager.hpp"


int main(int argc, char *argv[])
{
  CameraConnector *camCon = CameraConnector::getInstance();
  camCon->connectCameras(0, 1);
  //camCon->connectCameras(1, 1);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  
  DataManager dm;

  dm.startThreads(argc, argv);

  return dm.maingui(argc, argv);
}