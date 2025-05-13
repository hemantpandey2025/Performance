SmartQC()
{
	web_add_header("Access-Control-Request-Headers", 		"tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 		"GET");
	web_add_auto_header("Origin", 		"https://connectors.{P_Envname}.dsbu.cloud");
	web_add_auto_header("Sec-Fetch-Dest", 	"empty");
	web_add_auto_header("Sec-Fetch-Mode", 		"cors");
	web_add_auto_header("Sec-Fetch-Site", 		"same-site");

	lr_start_transaction("ESI_T02_AddNewConnection");
	
	web_custom_request("connectors_3", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connectors", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t142.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_auto_header("sec-ch-ua-mobile", 		"?0");
	web_add_auto_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_auto_header("tfs-platform-tenantalias", 		"connect_tst_perf");

	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"name\":\"SmartQCConnector\"",
		LAST);

	web_url("connectors_4", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connectors", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t143.inf", 
		"Mode=HTML", 
		LAST);

	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T02_AddNewConnection",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T02_AddNewConnection failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T02_AddNewConnection",LR_AUTO);

	lr_think_time(5);
	
	web_revert_auto_header("Origin");
	web_add_auto_header("Sec-Fetch-Site", 		"same-origin");

	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"app\": \"Basic authentication\"",
		LAST);
	
	lr_start_transaction("ESI_T06_SmartQC_ConnectApp");
	
	web_url("configure-connection.json_2", 
		"URL=https://connectors.{P_Envname}.dsbu.cloud/assets/configure-connection.json", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t144.inf", 
		"Mode=HTML", 
		LAST);

	web_revert_auto_header("tfs-platform-tenantalias");
	web_add_auto_header("Sec-Fetch-Site", 		"none");

	

	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T06_SmartQC_ConnectApp",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T06_SmartQC_ConnectApp failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T06_SmartQC_ConnectApp",LR_AUTO);

	lr_think_time(5);

	lr_save_string(lr_eval_string("PT_SmartQC_{VuserID}_{IterationNumber}_{Timestamp}"), "connectionName");
	
	/* Enter Details */
	
	web_revert_auto_header("sec-ch-ua");
	web_revert_auto_header("sec-ch-ua-mobile");
	web_revert_auto_header("sec-ch-ua-platform");
	web_add_header("Access-Control-Request-Headers", 		"content-type,tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 		"POST");
	web_add_auto_header("Origin", 		"https://connectors.{P_Envname}.dsbu.cloud");
	web_add_auto_header("Sec-Fetch-Site", 		"same-site");
	web_add_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_header("sec-ch-ua-mobile", 		"?0");
	web_add_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_header("tfs-platform-tenantalias", 	"connect_tst_perf");
	web_add_header("Access-Control-Request-Headers", 		"content-type,tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 		"POST");

	lr_start_transaction("ESI_T07_SmartQC_TestConnection");
	
	web_custom_request("test_5", 
		"URL=https://api.{P_Envname}.dsbu.cloud/smartqc/connections/test", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t148.inf", 
		"Mode=HTML", 
		LAST);

	web_add_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_header("sec-ch-ua-mobile", 		"?0");
	web_add_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_header("tfs-platform-tenantalias", 		"connect_tst_perf");
	
	web_reg_find("Search=Body",
	    "SaveCount=txtChk",
		"Text=\"status\":null,\"",
		LAST);
	
	lr_start_transaction("ESI_T07_01_SmartQC_TestConnection_API");
	
	web_custom_request("test_6", 
		"URL=https://api.{P_Envname}.dsbu.cloud/smartqc/connections/test", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t149.inf", 
		"Mode=HTML", 
		"EncType=application/json",
		"Body={\"endpoint\":\"https://tf.smart-qc.com\",\"description\":\"Desc_{connectionName}\",\"name\":\"{connectionName}\",\"authSchemeName\":\"Custom authentication\",\"credentialMap\":{\"accessKey\":\"AAACAFWhTrYAr0dpPqWs+j2I8ns6AKfuM0VOo\",\"secretKey\":\"Q6704D2rfa2Rpq/48dQeunFP3XpUTv4+WLpHdKeC9O7XDNOJDF3Gwz1GoI8Fm3ZAWnhTLX1i8yuaJP3UVNGBigLCane05rVzAGTAqYDt/vvrT5HOSB2W0Spqv0fCmWHVDiczbG29FH5lkKQDHYf3YowjarC8UBukIPbPz5R6wtOg0LB9Zco9M3zdh/1ZAkJU1Y7AMh8fC5GiwqWhgZCbONX4BiCv4SLmzJLl+a46qAvlspG\"},\"authSchemeId\":2,\"modifiedFields\":[\"secretKey\",\"accessKey\"],\"connectionID\":\"\"}",	 
		LAST);

	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T07_SmartQC_TestConnection",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T07_SmartQC_TestConnection failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T07_SmartQC_TestConnection",LR_AUTO);
	lr_end_transaction("ESI_T07_01_SmartQC_TestConnection_API",LR_AUTO);
	
	lr_think_time(5);
	
	web_add_header("Access-Control-Request-Headers", 		"content-type,tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 	"POST");

	lr_start_transaction("ESI_T08_SmartQC_AddConnection");


	
	web_custom_request("SmartQCConnector", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/SmartQCConnector", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t150.inf", 
		"Mode=HTML", 
		LAST);

	web_add_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_header("sec-ch-ua-mobile", 		"?0");
	web_add_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_header("tfs-platform-tenantalias", 	"connect_tst_perf");

	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"status\":\"CONNECTED\"",
		LAST);
	
	lr_start_transaction("ESI_T08_1_SmartQC_AddConnection_API");
	
	web_custom_request("SmartQCConnector_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/SmartQCConnector", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t151.inf", 
		"Mode=HTML", 
		"EncType=application/json",
		"Body={\"endpoint\":\"https://tf.smart-qc.com\",\"description\":\"Desc_{connectionName}\",\"name\":\"{connectionName}\",\"authSchemeName\":\"Custom authentication\",\"credentialMap\":{\"accessKey\":\"AAACAFWhTrYAr0dpPqWs+j2I8ns6AKfuM0VOo\",\"secretKey\":\"Q6704D2rfa2Rpq/48dQeunFP3XpUTv4+WLpHdKeC9O7XDNOJDF3Gwz1GoI8Fm3ZAWnhTLX1i8yuaJP3UVNGBigLCane05rVzAGTAqYDt/vvrT5HOSB2W0Spqv0fCmWHVDiczbG29FH5lkKQDHYf3YowjarC8UBukIPbPz5R6wtOg0LB9Zco9M3zdh/1ZAkJU1Y7AMh8fC5GiwqWhgZCbONX4BiCv4SLmzJLl+a46qAvlspG\"},\"authSchemeId\":2,\"modifiedFields\":[\"accessKey\",\"secretKey\"],\"connectionID\":\"\",\"status\":\"CONNECTED\",\"active\":true}",
		LAST);

	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T08_1_SmartQC_AddConnection_API",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T08_1_SmartQC_AddConnection_API failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T08_1_SmartQC_AddConnection_API",LR_AUTO);
	
	web_add_auto_header("Access-Control-Request-Headers", 		"tfs-platform-tenantalias");
	web_add_auto_header("Access-Control-Request-Method", 		"GET");

	lr_start_transaction("ESI_T08_2_DisplayConnections");

	web_custom_request("summary_15", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/summary", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t152.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("connections_29", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections?status=all&order=updatedon", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t153.inf", 
		"Mode=HTML", 
		LAST);



	web_revert_auto_header("Access-Control-Request-Headers");
	web_revert_auto_header("Access-Control-Request-Method");
	web_add_auto_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_auto_header("sec-ch-ua-mobile", 		"?0");
	web_add_auto_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_auto_header("tfs-platform-tenantalias", 		"connect_tst_perf");



	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"totalConnectionCount",
		LAST);
	
	web_url("summary_20", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/summary", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t161.inf", 
		"Mode=HTML", 
		LAST);

	web_url("connections_33", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections?status=all&order=updatedon", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t162.inf", 
		"Mode=HTML", 
		LAST);



	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T08_2_DisplayConnections",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T08_2_DisplayConnections failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T08_2_DisplayConnections",LR_AUTO);

	lr_end_transaction("ESI_T08_SmartQC_AddConnection", LR_AUTO);

	lr_output_message("%s", lr_eval_string("ESI_T08_1_SmartQC_AddConnection successful  connectionName: {connectionName} , UserName: {P_userName} ,Timestamp : {Timestamp}"));
	
	lr_think_time(5);

	

	return 0;
}
