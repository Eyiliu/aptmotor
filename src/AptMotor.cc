// Filename: AptMotor.cc
// Description: 
// Author: LIU Yi
// Copyright (C) 2014, LIU Yi, all rights reserved.
// Created: Sun Sep 14 00:07:19 2014 (+0800)
// Version: 
// Package-Requires: (PyAPT, python2.7)
// Last-Updated: Thu Jul  2 16:48:15 2015 (+0800)
//           By: LIU Yi
//     Update #: 35
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdarg.h>

#include <python2.7/Python.h>


#include <iostream> 
#include <string>

#include "AptMotor.hh"


std::vector<AptMotor *> AptMotor::motorCol;


AptMotor* AptMotor::apt_get_motor(std::string serial){
  for (std::vector<AptMotor *>::iterator it = motorCol.begin() ; 
       it != motorCol.end(); ++it){
    if(!((*it)->serial.compare(serial))){
      return *it;
    }
  }
  motorCol.push_back(new AptMotor(serial));
  return motorCol.back();
}

int AptMotor::apt_del_motor_all(){
  for (std::vector<AptMotor *>::iterator it = motorCol.begin() ; 
       it != motorCol.end(); ++it){
    delete *it;
    *it = NULL;
  }
  motorCol.clear();
  return 1;
} 


AptMotor::AptMotor(std::string ser):pinst(0),serial(ser),position_raw_dev(0){
  if(!Py_IsInitialized()){
      Py_Initialize();
  }

  PyObject *pmod, *pclass, *pargs;  
  pmod = PyImport_ImportModule("pyAPT"); 
  if(!pmod)
    std::cout<<"ERROR: pmod"<<std::endl;

  pclass = PyObject_GetAttrString(pmod, "Z8xx");
  if(!pclass)
    std::cout<<"ERROR: pclass"<<std::endl;
  Py_DECREF(pmod);

  pargs = Py_BuildValue("(ss)", serial.c_str(), "label");
  pinst = PyEval_CallObject(pclass, pargs);
  if(!pinst)
    std::cout<<"ERROR: inst"<<std::endl;
  Py_DECREF(pargs);
  Py_DECREF(pclass);

  std::cout<<"AptMotor created"<<std::endl;
  
}


AptMotor::~AptMotor(){
  Py_DECREF(pinst);
  std::cout<<"AptMotor deleted"<<std::endl;

}

int AptMotor::apt_home(){
  PyObject *pmeth, *pres;
  pmeth = PyObject_GetAttrString(pinst, "home");

  PyObject *pargs;

  pargs = Py_BuildValue("{s:d}", "offset", 0.3);
  pres = PyEval_CallObjectWithKeywords(pmeth, NULL, pargs);
  Py_DECREF(pargs);


  // pres = PyEval_CallObject(pmeth, NULL);
  // Py_DECREF(pmeth);
  Py_DECREF(pres);
  position_raw_dev = 0;

  return 1;
}

int AptMotor::apt_reset(){
  PyObject *pmeth, *pres;
  pmeth = PyObject_GetAttrString(pinst, "reset_parameters");
  pres = PyEval_CallObject(pmeth, NULL);
  Py_DECREF(pmeth);
  Py_DECREF(pres);
  return 1;
}

int AptMotor::apt_goto_raw(int pos_raw){
  PyObject *pmeth, *pres, *pargs;
  int pos_raw_tgt = pos_raw;
  if(pos_raw_tgt < 0)
    pos_raw_tgt = 0;

  std::cout<<"Go to position raw: "<<pos_raw_tgt<<std::endl;
  pmeth = PyObject_GetAttrString(pinst, "goto_raw");
  pargs = Py_BuildValue("(i)", pos_raw_tgt);
  pres = PyEval_CallObject(pmeth, pargs);
  Py_DECREF(pargs);
  Py_DECREF(pmeth);
  Py_DECREF(pres);
  position_raw_dev = pos_raw_tgt;
  return pos_raw_tgt;
  
}


double AptMotor::apt_goto(double pos){
  int enc = 34304;
  int pos_raw = pos*enc;
  int re = apt_goto_raw(pos_raw);
  return ((double) re)/enc;
}

int AptMotor::apt_move_raw(int dst_raw){
  int pos_raw = position_raw_dev + dst_raw;
  return apt_goto_raw(pos_raw);  
}

int AptMotor::apt_get_position_raw(){
  PyObject *pmeth, *pres, *pres_position_raw;
  int  position_raw;

  pmeth = PyObject_GetAttrString(pinst, "status");
  pres = PyEval_CallObject(pmeth, NULL);
  Py_DECREF(pmeth);
  pres_position_raw = PyObject_GetAttrString(pres, "position_apt");
  PyArg_Parse(pres_position_raw, "i", &position_raw);  
  Py_DECREF(pres);
  Py_DECREF(pres_position_raw);
  position_raw_dev = position_raw;
  return position_raw;
}


int AptMotor::apt_print_status(){
  PyObject *pmeth, *pres;
  PyObject *pres_position_real, *pres_position_raw, *pres_statusbits;
  double position_real;
  int position_raw;
  unsigned int statusbits;

  pmeth = PyObject_GetAttrString(pinst, "status");
  pres = PyEval_CallObject(pmeth, NULL);
  Py_DECREF(pmeth);

  pres_position_real = PyObject_GetAttrString(pres, "position");
  PyArg_Parse(pres_position_real, "d", &position_real);  
  Py_DECREF(pres_position_real);

  pres_position_raw = PyObject_GetAttrString(pres, "position_apt");
  PyArg_Parse(pres_position_raw, "i", &position_raw);  
  Py_DECREF(pres_position_raw);

  pres_statusbits = PyObject_GetAttrString(pres, "statusbits");
  PyArg_Parse(pres_statusbits, "I", &statusbits);  
  Py_DECREF(pres_statusbits);
  

  Py_DECREF(pres);

  position_raw_dev = position_raw;
  
  std::cout<<serial
	   <<"  position_real: "<< position_real 
	   <<"  position_raw: "<<position_raw
	   <<"  status_bits: "<<std::hex<< statusbits<< std::dec
	   <<std::endl;
  
  return 1;
}


std::string AptMotor::apt_get_serial(){
  return serial; 
};
