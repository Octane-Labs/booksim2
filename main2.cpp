#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <mcheck.h>
#include <stdlib.h>

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <czmq.h>

using namespace std;

int main( int argc, char **argv )
{
  // mtrace();
  // int threadCount = 0;
  int run_count = 0;
  zsock_t *rep = zsock_new_rep("tcp://*:9999");
  const char* REQ_STRING = "START BOOKSIM";
  const char* REP_STRING1 = "BOOKSIM OK";
  const char* REP_STRING2 = "EP OK. BOOKSIM STARTED";

  while(1) {
    char* req = zstr_recv(rep);
    string request = string(req);
    // cout<<request.compare(REQ_STRING)<<endl;
    if(request.compare(REQ_STRING) == 0) {
      // cout<<zstr_send(rep,REP_STRING1)<<endl;
      zstr_send(rep,REP_STRING1);
    } else {
      cout<<"Invalid command "<<request<<endl;
    }
    zstr_free(&req);
    req = zstr_recv(rep);
    cout<<"Received endpoint : "<<req<<endl;
    // gGPEndpoint = new char[128];
    // strcpy(gGPEndpoint,req);
    zstr_free(&req);
    cout<<"Sent start final ack"<<endl;
    zstr_send(rep,REP_STRING2);
    system("booksim2");
    run_count++;
  }

  zsock_destroy(&rep);

}
