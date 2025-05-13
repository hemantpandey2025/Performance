ListNotifications()
{
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"SaveCount=txtchk",
		"Text=notifications",
		LAST);	
		
	web_reg_save_param("C_state",
		"LB=notificationState\":\"",
		"RB=\"","ord=",
		LAST);
	
	web_reg_save_param("C_notificationId",
		"LB=\"notificationId\":\"",
		"RB=\"","ord=",
		LAST);
	
	lr_start_transaction("ENM_T02_getNotificationsList");

	web_custom_request("getNotificationsList_4", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/getNotificationsList", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t30.inf", 
		"Mode=HTML", 
		"EncType=application/json", 
		"Body={\"viewDismissed\":false,\"nextPageKey\":\"0:0\"}", 
		LAST);
		
	
	
	if(atoi(lr_eval_string("{txtChk}"))==0){
		
    lr_end_transaction("ENM_T02_getNotificationsList", LR_FAIL);
	lr_output_message("%s", lr_eval_string("ENM_T02_getNotificationsList failed. UserName: {P_userName} ,Timestamp : {Timestamp}"));
	lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 	
	
	lr_end_transaction("ENM_T02_getNotificationsList", LR_AUTO); 	

	lr_think_time(lr_get_attrib_double("TT"));
	
	return 0;
}
