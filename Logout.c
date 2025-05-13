Logout()
{
	
	/*****************************New Logout Code*******************************/
	
	web_add_auto_header("Accept", 
		"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Accept-Encoding", 
		"gzip, deflate, br");

	web_add_auto_header("Accept-Language", 
		"en-US,en;q=0.9");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Not_A Brand\";v=\"99\", \"Google Chrome\";v=\"109\", \"Chromium\";v=\"109\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");
		
	//web_add_header("Cookie",lr_eval_string("{platformSession}; {platformSession1}"));
	
	web_reg_find("Search=Body","SaveCount=Textcheck","Text/IC=<title>Logout Page</title>",LAST);
	
	lr_start_transaction("99_Logout");

	web_url("userhome.{P_Envname}.dsbu.cloud_2", 
		"URL=https://userhome.{P_Envname}.dsbu.cloud/?logout", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t39.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=https://auth.thermofisher.com/sdk.config.get?apiKey={apiKey}&httpStatusCodes=true", "Referer=https://www.qa.thermofisher.com/", ENDITEM, 
		LAST);

	web_add_auto_header("Sec-Fetch-Dest", 
		"iframe");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-site");

	web_url("Api.aspx_7", 
		"URL=https://auth.thermofisher.com/gs/webSdk/Api.aspx?apiKey={apiKey}&version=latest&build=15936", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://www.qa.thermofisher.com/", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/sdk.config.get?apiKey={ssoKey}&httpStatusCodes=true", "Referer=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=15936", ENDITEM, 
		LAST);

	web_add_cookie("gig_canary_ver_{ssoKey}=15936-3-28594710; DOMAIN=auth.thermofisher.com");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Accept", 
		"*/*");

	web_add_auto_header("Sec-Fetch-Mode", 
		"cors");

	web_add_auto_header("Sec-Fetch-Dest", 
		"empty");

	web_add_header("Origin", 
		"https://www.qa.thermofisher.com");
	
//	web_add_cookie("gmid={gmidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("ucid={ucidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("hasGmid=ver4; DOMAIN=auth.thermofisher.com");

	web_submit_data("accounts.logout", 
		"Action=https://auth.thermofisher.com/accounts.logout", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/javascript", 
		"Referer=https://www.qa.thermofisher.com/", 
		"Snapshot=t41.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=signIDs", "Value=true", ENDITEM, 
		"Name=APIKey", "Value={apiKey}", ENDITEM, 
		"Name=sdk", "Value=js_latest", ENDITEM, 
		"Name=login_token", "Value={logintoken}", ENDITEM, 
		"Name=authMode", "Value=cookie", ENDITEM, 
		"Name=pageURL", "Value=https://www.qa.thermofisher.com/identity/auth-ui/logout/logout.html?returnTo=https%3A%2F%2Fhome.{P_Envname}.dsbu.cloud", ENDITEM, 
		"Name=sdkBuild", "Value=15936", ENDITEM, 
		"Name=format", "Value=json", ENDITEM, 
		LAST);

	web_add_auto_header("Accept", 
		"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");

	web_add_auto_header("Sec-Fetch-Site", 
		"cross-site");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("home.{P_Envname}.dsbu.cloud_2", 
		"URL=https://home.{P_Envname}.dsbu.cloud/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://www.qa.thermofisher.com/", 
		"Snapshot=t42.inf", 
		"Mode=HTML", 
		LAST);
	
	web_add_auto_header("Accept", 
		"application/json, text/plain, */*");

	web_add_header("Origin", 
		"https://home.{P_Envname}.dsbu.cloud");

	web_add_auto_header("Sec-Fetch-Dest", 
		"empty");

	web_add_auto_header("Sec-Fetch-Mode", 
		"cors");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-site");

	web_url("v2_3", 
		"URL=https://api.{P_Envname}.dsbu.cloud/platformheader-anonymous/headerdata/v2", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://home.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t43.inf", 
		"Mode=HTML", 
		LAST);
	
	if(atoi(lr_eval_string("{Textcheck}"))==0)
	{
		lr_end_transaction("99_Logout", LR_FAIL);
		lr_output_message("%s", lr_eval_string("99_Logout failed. UserName: {P_userName} Timestamp : {Timestamp}"));		
		lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);	
	}
    
    lr_end_transaction("99_Logout", LR_AUTO);
	
	/***************************Logout code Ends********************************/
    
	return 0;
}
