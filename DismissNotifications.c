DismissNotifications()
{
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"SaveCount=txtchk",
		"Text=HTTP/1.1 200 OK",
		LAST);
		
	lr_start_transaction("ENM_T05_DismissNotification");
	
	web_custom_request("web_custom_request",
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/dismiss",
		"Method=PUT",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		"EncType=application/json; charset=utf-8",	
		"Body={\"notificationIds\":[\"{C_notificationId}\"]}", 
		LAST);

	
	if(atoi(lr_eval_string("{txtChk}"))==0){
		
    lr_end_transaction("ENM_T05_DismissNotification", LR_FAIL);
	lr_output_message("%s", lr_eval_string("ENM_T05_DismissNotification failed. UserName: {S01_NotificationAPIs_All_Flows_P_userName} ,Timestamp : {S01_NotificationAPIs_All_Flows_Timestamp}"));
	lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 	
	
	lr_end_transaction("ENM_T05_DismissNotification", LR_AUTO); 	

	lr_think_time(lr_get_attrib_double("TT"));
	
	return 0;
}
