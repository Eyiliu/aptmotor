// Filename: AptMotor.hh
// Description: 
// Author: LIU Yi
// Copyright (C) 2014, LIU Yi, all rights reserved.
// Created: Sun Sep 14 00:06:31 2014 (+0800)
// Version: 
// Package-Requires: (PyAPT, python2.7)
// Last-Updated: Thu Jul  2 16:45:03 2015 (+0800)
//           By: LIU Yi
//     Update #: 17
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

#ifndef	_APTMOTOR_HH
#define	_APTMOTOR_HH	1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <vector>

#include <python2.7/Python.h>


#include <TROOT.h>



class AptMotor;

class AptMotor{
public:
  AptMotor(std::string);
  virtual ~AptMotor();
  
  static AptMotor* apt_get_motor(std::string);
  static int apt_del_motor_all();

  int apt_reset();
  int apt_home();
  int apt_goto_raw(int);
  int apt_move_raw(int);
  int apt_get_position_raw();
  // bool apt_ishomed();

  int apt_print_status();
  std::string apt_get_serial();

  double apt_goto(double);
  // double apt_move(double);
  // double apt_get_position();

private:
  PyObject *pinst;
  std::string serial;
  int position_raw_dev;

  static std::vector<AptMotor *> motorCol;

  ClassDef(AptMotor,0);

};




#endif	/* AptMotor.hh */
