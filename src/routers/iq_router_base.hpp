// $Id$

/*
Copyright (c) 2007-2009, Trustees of The Leland Stanford Junior University
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this 
list of conditions and the following disclaimer in the documentation and/or 
other materials provided with the distribution.
Neither the name of the Stanford University nor the names of its contributors 
may be used to endorse or promote products derived from this software without 
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR 
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _IQ_ROUTER_BASE_HPP_
#define _IQ_ROUTER_BASE_HPP_

#include <string>
#include <queue>
#include <set>
#include <iostream>

#include "router.hpp"
#include "routefunc.hpp"
#include "pipefifo.hpp"
#include "trafficmanager.hpp"

using namespace std;

class VC;
class Flit;
class Credit;
class Buffer;
class BufferState;
class SwitchMonitor;
class BufferMonitor;

class IQRouterBase : public Router {

protected:
  int  _vcs ;

  //if a vc is in the vc::routing state, it is inserted here until routing_delay is up
  queue<pair<int, int> > _routing_vcs;
  set<pair<int, int> > _vcalloc_vcs;  

  vector<Buffer *> _buf;
  vector<BufferState *> _next_buf;

  tRoutingFunction   _rf;

  PipelineFIFO<Flit> * _crossbar_pipe;
  PipelineFIFO<Credit> * _credit_pipe;
  
  int _routing_delay;
  int _vc_alloc_delay;
  int _sw_alloc_delay;
  
  //  vector<queue<Flit *> > _input_buffer;
  vector<queue<Flit *> > _output_buffer;

  vector<queue<Credit *> > _in_cred_buffer;
  //vector<queue<Credit *> > _out_cred_buffer;

  int _hold_switch_for_packet;
  vector<int> _switch_hold_in;
  vector<int> _switch_hold_out;
  vector<int> _switch_hold_vc;

  vector<int> _received_flits;
  vector<int> _sent_flits;

  void _ReceiveFlits( );
  void _ReceiveCredits( );

  virtual void _InputQueuing( );
  virtual void _Route( );
  virtual void _Alloc( ) = 0;
  virtual void _OutputQueuing( );

  void _SendFlits( );
  void _SendCredits( );
  
  // ----------------------------------------
  //
  //   Router Power Modellingyes
  //
  // ----------------------------------------

  SwitchMonitor * _switchMonitor ;
  BufferMonitor * _bufferMonitor ;
  
public:
  IQRouterBase( const Configuration& config,
	    Module *parent, const string & name, int id,
	    int inputs, int outputs );
  
  virtual ~IQRouterBase( );
  
  virtual void ReadInputs( );
  virtual void InternalStep( );
  virtual void WriteOutputs( );
  
  void Display( ) const;
  virtual int GetCredit(int out, int vc_begin, int vc_end ) const;
  virtual int GetBuffer(int i = -1) const;
  virtual int GetReceivedFlits(int i = -1) const;
  virtual int GetSentFlits(int o = -1) const;
  virtual void ResetFlitStats();

  const SwitchMonitor* GetSwitchMonitor() const {return _switchMonitor;}
  const BufferMonitor* GetBufferMonitor() const {return _bufferMonitor;}
};

#endif
