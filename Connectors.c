Connectors()
{

	web_reg_find("Text=Connectors", 
		LAST);

	web_add_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-site");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_start_transaction("ESI_T01_ClickConnectors");

	web_url("connectors.{P_Envname}.dsbu.cloud", 
		"URL=https://connectors.{P_Envname}.dsbu.cloud/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t87.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("Origin", 
		"https://connectors.{P_Envname}.dsbu.cloud");

	web_add_auto_header("Sec-Fetch-Dest", 
		"empty");

	web_add_auto_header("Sec-Fetch-Mode", 
		"cors");

	web_reg_find("Search=Body",
		"Text=\"Connect Platform - Connectors\"",
		LAST);

	web_url("v2_3", 
		"URL=https://api.{P_Envname}.dsbu.cloud/platformheader/headerdata/v2", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t88.inf", 
		"Mode=HTML", 
		LAST);

	web_revert_auto_header("sec-ch-ua");

	web_revert_auto_header("sec-ch-ua-mobile");

	web_revert_auto_header("sec-ch-ua-platform");

	web_add_auto_header("Access-Control-Request-Headers", 
		"tfs-platform-tenantalias");

	web_add_auto_header("Access-Control-Request-Method", 
		"GET");

	web_custom_request("summary", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/summary", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t89.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("connections", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections?status=all&order=updatedon", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t90.inf", 
		"Mode=HTML", 
		LAST);



	web_revert_auto_header("Access-Control-Request-Headers");

	web_revert_auto_header("Access-Control-Request-Method");

	web_add_auto_header("sec-ch-ua", 
		"\"Google Chrome\";v=\"95\", \"Chromium\";v=\"95\", \";Not A Brand\";v=\"99\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");

	web_add_auto_header("tfs-platform-tenantalias", 
		"connect_tst_perf");

	//{"totalConnectionCount":10,"activeConnectionCount":10,"inactiveConnectionCount":0,"invalidConnectionCount":0,"tenantName":null}
	
	web_reg_find("Search=Body",
		"SaveCount=txtChk",
		"Text=\"totalConnectionCount",
		LAST);

	web_url("summary_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections/summary", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t92.inf", 
		"Mode=HTML", 
		LAST);

	web_url("connections_3", 
		"URL=https://api.{P_Envname}.dsbu.cloud/connector/connections?status=all&order=updatedon", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://connectors.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t93.inf", 
		"Mode=HTML", 
		LAST);



	if(atoi(lr_eval_string("{txtChk}"))==0){
		lr_end_transaction("ESI_T01_ClickConnectors",LR_FAIL);
		lr_output_message("%s", lr_eval_string("ESI_T01_ClickConnectors failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("ESI_T01_ClickConnectors",LR_AUTO);

	lr_think_time(5);

	return 0;
}
