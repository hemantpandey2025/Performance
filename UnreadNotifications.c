UnreadNotifications()
{
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"SaveCount=txtchk",
		"Text=notificationCount",
		LAST);
	
	//{"notificationCount":3}
	web_reg_save_param("C_notificationCount",
	    "LB=\"notificationCount\":",
	    "RB=}",
	    LAST);
	
	lr_start_transaction("ENM_T01_getUnreadNotificationCount");

	web_url("getUnreadNotificationCount",
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/getUnreadNotificationCount",		
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/",
		"Snapshot=t26.inf", 
		"Mode=HTML", 
		LAST);  
	
	if(atoi(lr_eval_string("{txtChk}"))==0){
   		lr_end_transaction("ENM_T01_getUnreadNotificationCount", LR_FAIL);
		lr_output_message("%s", lr_eval_string("T01_getUnreadNotificationCount failed. UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	
	lr_end_transaction("ENM_T01_getUnreadNotificationCount", LR_AUTO);  
	lr_output_message("%s", lr_eval_string("Txn 'T01_getUnreadNotificationCount' passed for UserName: {P_userName} , Unread Notification Count: {C_notificationCount} , Timestamp : {Timestamp}"));
	
	lr_think_time(lr_get_attrib_double("TT"));

	return 0;
}
