#pragma once

#define MAX_REQUEST_SIZE 102400
#define BUFFER_SIZE 1024
// #define REDYTOWRITE 1

//request status
#define NOTREADY 0
#define REQ_HEADR_DONE 1
#define READYTO_RES 2
#define SEND_ERROR 10
//response status
#define NOTREADYTOWRITE 3
#define HEADER_DONE 4
#define BODY_DONE 5

//body type
#define transfer_encoding 6
#define content_length 7
#define ERROR 8
#define NOT_ALLOWD_METHOD 9
//error page
#define ERROR_400 400  //Bad Request
#define ERROR_501 501  //Not Implemented
//25306036