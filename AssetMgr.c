AssetMgr()
{
	web_add_header("Access-Control-Request-Headers", 		"tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 		"GET");
	web_add_auto_header("Origin", 		"https://connectors.{P_Envname}.dsbu.cloud");
	web_add_auto_header("Sec-Fetch-Dest", 		"empty");
	web_add_auto_header("Sec-Fetch-Mode", 		"cors");
	web_add_auto_header("Sec-Fetch-Site", 		"same-site");

	lr_start_transaction("ESI_T02_AddNewConnection");
	
	web_custom_request("connectors", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connectors", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t96.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_auto_header("sec-ch-ua-mobile", 		"?0");
	web_add_auto_header("sec-ch-ua-platform",		"\"Windows\"");
	web_add_auto_header("tfs-platform-tenantalias", 		"connect_tst_perf");

	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"name\":\"AssetManagerConnector\"",
		LAST);

	web_url("connectors_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connectors", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t97.inf", 
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
	web_add_auto_header("Sec-Fetch-Site",		"same-origin");

	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"app\": \"Basic authentication\"",
		LAST);
	
	lr_start_transaction("ESI_T03_AssetManager_ConnectApp");

	web_url("configure-connection.json", 
		"URL=https://connectors.{P_Envname}.dsbu.cloud/assets/configure-connection.json", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t98.inf", 
		"Mode=HTML",
		LAST);

	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T03_AssetManager_ConnectApp",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T03_AssetManager_ConnectApp failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T03_AssetManager_ConnectApp",LR_AUTO);

	lr_think_time(5);

	lr_save_string(lr_eval_string("PT_AssetMgr_{VuserID}_{IterationNumber}_{Timestamp}"), "connectionName");
	
	/* Enter Details & click Test Connection */

	web_revert_auto_header("sec-ch-ua");
	web_revert_auto_header("sec-ch-ua-mobile");
	web_revert_auto_header("sec-ch-ua-platform");
	web_revert_auto_header("tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Headers", 		"content-type,tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 		"POST");
	web_add_auto_header("Origin", 		"https://connectors.{P_Envname}.dsbu.cloud");
	web_add_auto_header("Sec-Fetch-Site", 	"same-site");

	lr_start_transaction("ESI_T04_AssetManager_TestConnection");
	
	web_custom_request("test", 
		"URL=https://api.{P_Envname}.dsbu.cloud/assetmanager/connections/test", 
		"Method=OPTIONS", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t209.inf", 
		"Mode=HTML", 
		LAST);
	


	web_add_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_header("sec-ch-ua-mobile", 		"?0");
	web_add_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_header("tfs-platform-tenantalias", 		"connect_tst_perf");

	
	//Custom authentication
	//\"status\":null,\"
	web_reg_find("Search=Body",
	    "SaveCount=txtChk",
		"Text=\"status\":null,\"",
		LAST);
	
	lr_start_transaction("ESI_T04_01_AssetManager_TestConnection_API");
	
	web_custom_request("test_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/assetmanager/connections/test", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t210.inf", 
		"Mode=HTML", 
		"EncType=application/json",
		"Body={\"endpoint\":\"https://stage-api.thermofisher.com/api/ecosystem/uls-ams-service/connector-gateway\",\"description\":\"Desc_{connectionName}\",\"name\":\"{connectionName}\",\"authSchemeName\":\"OAuth 2.0 authentication\",\"credentialMap\":{\"identityProvider\":\"internalIDP\"},\"authSchemeId\":3,\"modifiedFields\":[\"identityProvider\"],\"connectionID\":\"\"}",		
	//	"Body={\"endpoint\":\"https://test-api.thermofisher.com/api/ecosystem/uls-ams-service/connector-gateway\",\"description\":\"Desc_{connectionName}\",\"name\":\"{connectionName}\",\"authSchemeName\":\"OAuth 2.0 authentication\",\"credentialMap\":{\"identityProvider\":\"internalIDP\"},\"authSchemeId\":3}", 
		LAST);



	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T04_AssetManager_TestConnection",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T04_AssetManager_TestConnection failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T04_01_AssetManager_TestConnection_API",LR_AUTO);
	lr_end_transaction("ESI_T04_AssetManager_TestConnection",LR_AUTO);

	lr_think_time(5);

	web_add_header("Access-Control-Request-Headers", 		"content-type,tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 	"POST");

	lr_start_transaction("ESI_T05_AssetManager_AddConnection");

	
	web_custom_request("AssetManagerConnector_3", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/AssetManagerConnector", 
		"Method=OPTIONS", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t211.inf", 
		"Mode=HTML", 
		LAST);
	


	web_add_header("sec-ch-ua", 		"\" Not A;Brand\";v=\"99\", \"Chromium\";v=\"102\", \"Google Chrome\";v=\"102\"");
	web_add_header("sec-ch-ua-mobile", 		"?0");
	web_add_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_header("tfs-platform-tenantalias", 		"connect_tst_perf");

	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"status\":\"CONNECTED\"",
		LAST);
	
	lr_start_transaction("ESI_T05_1_AssetManager_AddConnection_API");

	web_custom_request("AssetManagerConnector_4", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/AssetManagerConnector", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t212.inf", 
		"Mode=HTML", 
		"EncType=application/json", 
		"Body={\"endpoint\":\"https://stage-api.thermofisher.com/api/ecosystem/uls-ams-service/connector-gateway\",\"description\":\"Desc_{connectionName}\",\"name\":\"{connectionName}\",\"authSchemeName\":\"OAuth 2.0 authentication\",\"credentialMap\":{\"identityProvider\":\"internalIDP\"},\"authSchemeId\":3,\"modifiedFields\":[\"identityProvider\"],\"connectionID\":\"\"}",
	//	"Body={\"endpoint\":\"https://test-api.thermofisher.com/api/ecosystem/uls-ams-service/connector-gateway\",\"description\":\"Desc_{connectionName}\",\"name\":\"{connectionName}\",\"authSchemeName\":\"OAuth 2.0 authentication\",\"credentialMap\":{\"identityProvider\":\"internalIDP\"},\"authSchemeId\":3,\"status\":\"CONNECTED\",\"active\":true}", 
		LAST);
	


	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T05_1_AssetManager_AddConnection_API",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T05_1_AssetManager_AddConnection_API failed. UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T05_1_AssetManager_AddConnection_API",LR_AUTO);
	
	web_add_header("Access-Control-Request-Headers", 		"tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 		"GET");
	
	lr_start_transaction("ESI_T05_2_DisplayConnections");

	web_custom_request("summary_3", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/summary", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t103.inf", 
		"Mode=HTML", 
		LAST);


	web_add_header("Access-Control-Request-Headers", 		"tfs-platform-tenantalias");
	web_add_header("Access-Control-Request-Method", 		"GET");

	web_custom_request("connections_6", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections?status=all&order=updatedon", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t105.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("sec-ch-ua", 		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");
	web_add_auto_header("sec-ch-ua-mobile", 		"?0");
	web_add_auto_header("sec-ch-ua-platform", 		"\"Windows\"");
	web_add_auto_header("tfs-platform-tenantalias", 		"connect_tst_perf");

	web_url("connections_7", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections?status=all&order=updatedon", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t106.inf", 
		"Mode=HTML", 
		LAST);



	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"totalConnectionCount",
		LAST);
	
	web_url("summary_6", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/summary", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t108.inf", 
		"Mode=HTML", 
		LAST);



	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T05_2_DisplayConnections",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T05_2_DisplayConnections failed. UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T05_2_DisplayConnections",LR_AUTO);
	
	lr_end_transaction("ESI_T05_AssetManager_AddConnection", LR_AUTO);

	lr_output_message("%s", lr_eval_string("ESI_T05_1_AssetManager_AddConnection successful  connectionName: {connectionName} , UserName: {P_userName} ,Timestamp : {Timestamp}"));
	
	lr_think_time(5);

	

	

	return 0;
}
