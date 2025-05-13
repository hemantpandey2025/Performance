SendNotifications()
{
	
	web_add_header("accept",
		"application/json");

	web_add_header("Sprox-Service",
		"DHA_NM_SVC");

	web_add_header("Sprox-Service-Roles",
		"ROLE_SERVICE");

	web_add_header("Content-Type",
		"application/json");	
	
	//{"notifications":[]}
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"SaveCount=txtchk",
		"Text=notifications",
		LAST);
	
	lr_start_transaction("ENM_T06_SendNotification");
	
	web_custom_request("web_custom_request",
		"URL=https://enm-automation.perf-tst.dsbu.cloud/nm/nmsvc/api/system/v4/notifications", //api.perf-tst  
	//	"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/system/v4/notifications",
		"Method=POST",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		"Body={\r\n"
		"  \"sourceId\": \"ceperfmaintenant\",\r\n"
		"  \"principalIds\": [\r\n"
		"    \"{C_UID}\"\r\n"
		"  ],\r\n"
		"  \"message\": {\r\n"
		"    \"subject\": \"Hello Subject\",\r\n"
		"    \"title\": \"Hello $owner_user_name\",\r\n"
		"    \"body\": \"Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer nonummy tincidunt mi. Etiam nec nulla. \\n"
		"Ut eros. Etiam vel dui id purus adipiscing porttitor. \\n"
		"Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus.\\n"
		" \\n"
		"Pellentesque est. Fusce pulvinar turpis vel sem. \\n"
		" File ${file_name} is available for sharing to\",\r\n"
		"    \"action\": {\r\n"
		"      \"caption\": \"Go to Thermo Fisher page\",\r\n"
		"      \"url\": \"http://www.thermofisher.com\"\r\n"
		"    }\r\n"
		"  },\r\n"
		"  \"messageParams\": {\r\n"
		"    \"owner_user_name\": \"PerfTestUser\",\r\n"
		"    \"file_name\": \"Blood_test_results.txt\"\r\n"
		"  },\r\n"
		"  \"templateId\": \"2a7cfabc-f3c3-4815-b9e1-2a8d65d842a2\",\r\n"
		"  \"type\": \"application\",\r\n"
		"  \"category\": \"normal\",\r\n"
		"  \"priority\": \"high\"\r\n"
		"}",
		LAST);
	
	if(atoi(lr_eval_string("{txtchk}"))==0){
		
    lr_end_transaction("ENM_T06_SendNotification", LR_FAIL);
	lr_output_message("%s", lr_eval_string("ENM_T06_SendNotification failed. UserName: {S01_NotificationAPIs_All_Flows_P_userName} ,Timestamp : {S01_NotificationAPIs_All_Flows_Timestamp}"));
	lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	
	} 	
	
	lr_end_transaction("ENM_T06_SendNotification", LR_AUTO); 	

	lr_think_time(lr_get_attrib_double("TT"));
	
	
	
	return 0;
}
