SampleMgr()
{
	web_add_header("Access-Control-Request-Headers", 		"tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 		"GET");
	web_add_auto_header("Origin", 		"https://connectors.{P_Envname}.dsbu.cloud");
	web_add_auto_header("Sec-Fetch-Dest", 		"empty");
	web_add_auto_header("Sec-Fetch-Mode", 		"cors");
	web_add_auto_header("Sec-Fetch-Site", 		"same-site");

	lr_start_transaction("ESI_T02_AddNewConnection");

	web_custom_request("connectors_5", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connectors", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t214.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_auto_header("sec-ch-ua-mobile", 		"?0");
	web_add_auto_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_auto_header("tfs-platform-tenantalias", 		"connect_tst_perf");

	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"name\":\"SampleManagerConnector\"",
		LAST);

	web_url("connectors_6", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connectors", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t215.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("ESI_T02_AddNewConnection",LR_AUTO);

	lr_think_time(5);
	
	web_revert_auto_header("Origin");
	web_add_auto_header("Sec-Fetch-Site", 		"same-origin");

	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"app\": \"Basic authentication\"",
		LAST);
	
	lr_start_transaction("ESI_T09_SampleManager_ConnectApp");
	
	web_url("configure-connection.json_3", 
		"URL=https://connectors.{P_Envname}.dsbu.cloud/assets/configure-connection.json", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t216.inf", 
		"Mode=HTML", 
		LAST);

	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T09_SampleManager_ConnectApp",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T09_SampleManager_ConnectApp failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T09_SampleManager_ConnectApp",LR_AUTO);

	lr_think_time(5);

	lr_save_string(lr_eval_string("PT_SampleMgr_{VuserID}_{IterationNumber}_{Timestamp}"), "connectionName");
	
	/* Enter Details */

	web_revert_auto_header("sec-ch-ua");
	web_revert_auto_header("sec-ch-ua-mobile");
	web_revert_auto_header("sec-ch-ua-platform");
	web_revert_auto_header("tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Headers", 		"content-type,tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 		"POST");
	web_add_auto_header("Origin", 		"https://connectors.{P_Envname}.dsbu.cloud");
	web_add_auto_header("Sec-Fetch-Site", 		"same-site");

	lr_start_transaction("ESI_T10_SampleManager_TestConnection");
	
	web_custom_request("test_7", 
		"URL=https://api.{P_Envname}.dsbu.cloud/samplemanager/connections/test", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t217.inf", 
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
	
	lr_start_transaction("ESI_T10_01_SampleManager_TestConnection_API");
	
	web_custom_request("test_8", 
		"URL=https://api.{P_Envname}.dsbu.cloud/samplemanager/connections/test", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t218.inf", 
		"Mode=HTML", 
		"EncType=application/json",
		"Body={\"endpoint\":\"http://15.206.45.207:56105\",\"description\":\"Desc_{connectionName}\",\"name\":\"{connectionName}\",\"authSchemeName\":\"Basic authentication\",\"credentialMap\":{\"password\":\"PerSistent\",\"username\":\"CEUSER\"},\"authSchemeId\":1,\"modifiedFields\":[\"username\",\"password\"],\"connectionID\":\"\"}",
		LAST);

	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T10_SampleManager_TestConnection",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T10_SampleManager_TestConnection failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T10_SampleManager_TestConnection",LR_AUTO);
	lr_end_transaction("ESI_T10_01_SampleManager_TestConnection_API",LR_AUTO);

	lr_think_time(5);
	
	web_add_header("Access-Control-Request-Headers", 		"content-type,tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 	"POST");
	
	lr_start_transaction("ESI_T11_SampleManager_AddConnection");

		
	web_custom_request("SampleManagerConnector", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/SampleManagerConnector", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t219.inf", 
		"Mode=HTML", 
		LAST);

	web_add_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_header("sec-ch-ua-mobile", 		"?0");
	web_add_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_header("tfs-platform-tenantalias", 		"connect_tst_perf");

	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"status\":\"CONNECTED\"",
		LAST);
	
	lr_start_transaction("ESI_T11_1_SampleManager_AddConnection_API");
	
	web_custom_request("SampleManagerConnector_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/SampleManagerConnector", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t220.inf", 
		"Mode=HTML", 
		"EncType=application/json",
		"Body={\"endpoint\":\"http://15.206.45.207:56105\",\"description\":\"Desc_{connectionName}\",\"name\":\"{connectionName}\",\"authSchemeName\":\"Basic authentication\",\"credentialMap\":{\"password\":\"PerSistent\",\"username\":\"CEUSER\"},\"authSchemeId\":1,\"modifiedFields\":[\"username\",\"password\"],\"connectionID\":\"\",\"status\":\"CONNECTED\",\"active\":true}",
		LAST);

	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T11_1_SampleManager_AddConnection_API",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T11_1_SampleManager_AddConnection_API failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T11_1_SampleManager_AddConnection_API",LR_AUTO);
	
	
	web_add_auto_header("Access-Control-Request-Headers", 		"tfs-platform-tenantalias");
	web_add_auto_header("Access-Control-Request-Method", 		"GET");

	lr_start_transaction("ESI_T11_2_DisplayConnections");

	web_custom_request("summary_33", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/summary", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t221.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("connections_69", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections?status=all&order=updatedon", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t222.inf", 
		"Mode=HTML", 
		LAST);



	web_revert_auto_header("Access-Control-Request-Headers");
	web_revert_auto_header("Access-Control-Request-Method");
	web_add_auto_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_auto_header("sec-ch-ua-mobile", 		"?0");
	web_add_auto_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_auto_header("tfs-platform-tenantalias", 		"connect_tst_perf");

	web_url("summary_36", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/summary", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t227.inf", 
		"Mode=HTML", 
		LAST);

	web_url("connections_72", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections?status=all&order=updatedon", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t228.inf", 
		"Mode=HTML", 
		LAST);


	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T11_2_DisplayConnections",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T11_2_DisplayConnections failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T11_2_DisplayConnections",LR_AUTO);	
	lr_end_transaction("ESI_T11_SampleManager_AddConnection", LR_AUTO);

	lr_output_message("%s", lr_eval_string("ESI_T11_1_SampleManager_AddConnection successful  connectionName: {connectionName} , UserName: {P_userName} ,Timestamp : {Timestamp}"));
	
	lr_think_time(5);
	
	

	return 0;
}
