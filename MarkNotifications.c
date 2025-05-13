MarkNotifications()
{
	web_add_header("Access-Control-Request-Headers", 
		"content-type");

	web_add_header("Access-Control-Request-Method", 
		"PUT");
	
	lr_save_string(lr_eval_string("{C_state}"),"Cstat");
	
	lr_save_string("UNREAD", "Cstate2");
	
	if(strcmp(lr_eval_string("{Cstat}"),lr_eval_string("{Cstate2}")) ==0)
		
	{
	       
	lr_start_transaction("ENM_T03_MarkAsRead"); //https://userhome.ce-perf-main.dsbu.cloud/
		
	web_custom_request("read", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/read", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t49.inf", 
		"Mode=HTML", 
		LAST);
		
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"SaveCount=readChk",
		"Text=\"status\":\"HTTP/1.1 200 OK\"",
		LAST);

	web_custom_request("read_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/read", 
		"Method=PUT", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json",
		"EncType=application/json; charset=utf-8",
		"Referer=https://api.{P_Envname}.dsbu.cloud/nm/api-doc/index.html",
		"Snapshot=t50.inf", 
		"Mode=HTML",
		"Body={\n  \"notificationIds\": [\n    \"{C_notificationId}\"\n  ]\n}",
		LAST);	
		
	lr_end_transaction("ENM_T03_MarkAsRead", LR_AUTO); 

	lr_think_time(lr_get_attrib_double("TT"));

	lr_start_transaction("ENM_T04_MarkAsUnRead");
		
	web_custom_request("read", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/unread", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t121.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"SaveCount=unReadChk",
		"Text=\"status\":\"HTTP/1.1 200 OK\"",
		LAST);
	
	web_custom_request("unread_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/unread", 
		"Method=PUT", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json",
		"Referer=https://api.{P_Envname}.dsbu.cloud/nm/api-doc/index.html",
		"EncType=application/json; charset=utf-8",		
		"Snapshot=t122.inf", 
		"Mode=HTML", 
		"Body={\n  \"notificationIds\": [\n    \"{C_notificationId}\"\n  ]\n}",
		LAST);
		
	lr_end_transaction("ENM_T04_MarkAsUnRead", LR_AUTO);  
			
	} 
	else if(strcmp(lr_eval_string("{Cstat}"),lr_eval_string("READ")) ==0)
	{
	
	lr_start_transaction("ENM_T04_MarkAsUnRead");
		
	web_custom_request("read", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/unread", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t121.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"SaveCount=unReadChk",
		"Text=\"status\":\"HTTP/1.1 200 OK\"",
		LAST);
	
web_custom_request("unread_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/unread", 
		"Method=PUT", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://api.{P_Envname}.dsbu.cloud/nm/api-doc/index.html",
		"EncType=application/json; charset=utf-8",		
		"Snapshot=t122.inf", 
		"Mode=HTML", 
		"Body={\n  \"notificationIds\": [\n    \"{C_notificationId}\"\n  ]\n}",
		LAST);
		
	lr_end_transaction("ENM_T04_MarkAsUnRead", LR_AUTO); 
	
	lr_think_time(lr_get_attrib_double("TT"));
	
	lr_start_transaction("ENM_T03_MarkAsRead");
		
	web_custom_request("read", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/read", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t49.inf", 
		"Mode=HTML", 
		LAST);
		
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"SaveCount=readChk",
		"Text=\"status\":\"HTTP/1.1 200 OK\"",
		LAST);


		web_custom_request("read_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/read", 
		"Method=PUT", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json",
		"EncType=application/json; charset=utf-8",
		"Referer=https://api.{P_Envname}.dsbu.cloud/nm/api-doc/index.html",
		"Snapshot=t50.inf", 
		"Mode=HTML",
		"Body={\n  \"notificationIds\": [\n    \"{C_notificationId}\"\n  ]\n}",
		LAST);
		
	lr_end_transaction("ENM_T03_MarkAsRead", LR_AUTO); 
	
	}
	
	else{
	lr_output_message("%s", lr_eval_string("No notifications for UserName: {P_userName} ,Timestamp : {Timestamp}"));
	
	}
	
	lr_think_time(lr_get_attrib_double("TT"));
	
	return 0;
}
