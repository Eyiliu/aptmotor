// Filename: rootlogon.C
// Description: 
// Author: LIU Yi
// Copyright (C) 2014, LIU Yi, all rights reserved.
// Created: Thu Jun 18 01:25:35 2015 (+0800)
// Version: 
// Package-Requires: ()
// Last-Updated: Thu Jul  2 16:26:15 2015 (+0800)
//           By: LIU Yi
//     Update #: 2
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
// 
// 

{
  stringstream ss_loadlib;
  string wkfd = gSystem->WorkingDirectory();
  wkfd.erase(wkfd.find_last_of('/'));
  ss_loadlib <<wkfd.c_str()<<"/libaptmotor.so";
  gSystem->Load(ss_loadlib.str().c_str());
  std::cout<<"rootlogon.C >> Load "<<ss_loadlib.str().c_str() <<std::endl<<std::endl;

}
