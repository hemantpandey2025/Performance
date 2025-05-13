Login()
{
	
   web_cleanup_cookies();
	 
    web_add_header("Sec-Fetch-Site", 		"none");
	web_add_auto_header("Sec-Fetch-Mode", 		"navigate");
	web_add_auto_header("Sec-Fetch-User", 		"?1");
	web_add_auto_header("Upgrade-Insecure-Requests", 		"1");	
	
	
	web_reg_find("Text=Connect Platform","Savecount=txtChk","Fail=NotFound",LAST);
	
	lr_start_transaction("01_Homepage");

	web_url("{URL}", 
		"URL=https://{URL}/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		EXTRARES, 
		LAST);

	web_add_header("Origin", 		"https://home.{P_Envname}.dsbu.cloud");
	web_add_header("Sec-Fetch-Dest", 		"empty");
	web_add_header("Sec-Fetch-Mode", 		"cors");
	web_add_auto_header("Sec-Fetch-Site", 		"same-site");

	web_url("headerdata", 
		"URL=https://api.{P_Envname}.dsbu.cloud/platformheader-anonymous/headerdata/v2", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://home.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		EXTRARES,
		LAST);

	if(atoi(lr_eval_string("{txtChk}"))==0){
		
    lr_end_transaction("01_Homepage", LR_FAIL);
	lr_output_message("%s", lr_eval_string("01_Homepage failed. UserName: {P_userName} ,Timestamp : {Timestamp}"));
	
	lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
		
	lr_end_transaction("01_Homepage", LR_AUTO);
	
	lr_think_time(lr_get_attrib_double("TT"));
	
	
	/* Click Sign IN */
	
	web_reg_save_param_ex("ParamName=apiKey","LB=gigya.js?apiKey=","RB=\"",SEARCH_FILTERS,"Scope=BODY","IgnoreRedirections=No","RequestUrl=*/account-center/proxy.html?*",LAST);
	
	web_reg_save_param_ex("ParamName=context","LB=context=","RB=&client_id",SEARCH_FILTERS,"Scope=Headers","IgnoreRedirections=No","RequestUrl=*/authorize*",LAST);
	
	web_reg_save_param_ex("ParamName=client_id","LB=client_id=","RB=&mode=login&scope=openid+profile+email+tenant",SEARCH_FILTERS,"Scope=Headers","IgnoreRedirections=No",LAST);
	
   //web_reg_save_param_ex("ParamName=client_id","LB=client_id=","RB=\r\n",SEARCH_FILTERS,"Scope=Headers","IgnoreRedirections=No",LAST);
	
	web_reg_find("Search=Body","SaveCount=txtChk","Text/IC=<title>Sign In",LAST);
	
	web_reg_find("Search=Body","SaveCount=SigninPage","Text/IC=signin-identifier",LAST);
	
   lr_start_transaction("03_ClickSignIn");

	web_url("userhome.{P_Envname}.dsbu.cloud", 
		"URL=https://userhome.{P_Envname}.dsbu.cloud/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://home.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t193.inf", 
		"Mode=HTML", 
		LAST);

	web_url("contextData", 
		"URL=https://auth.thermofisher.com/oidc/op/v1.0/{apiKey}/contextData?oidc_context={context}&client_id={client_id}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t194.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/js/gigya.oidc.js?apiKey={apiKey}", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
		//"Url=https://qa-identity.thermofisher.com/account-center/images/loading-wheel2-1742281383067.svg", "Referer=https://qa-identity.thermofisher.com/account-center/proxy.html?context={context}&client_id={client_id}&mode=login&scope=openid+profile+email+tenant", ENDITEM, 
		"Url=/sdk.config.get?apiKey={apiKey}&httpStatusCodes=true&ver=1742483880000", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
		LAST);
   
   web_reg_save_param_ex("ParamName=ssoKey","LB=\"ssoKey\": \"","RB=\",",SEARCH_FILTERS,LAST);

	web_url("Api.aspx", 
		"URL=https://auth.thermofisher.com/gs/webSdk/Api.aspx?apiKey={apiKey}&version=latest&build=17112&serviceName=apiService", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t195.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/sdk.config.get?apiKey={apiKey}&httpStatusCodes=true&ver=1742483880000", "Referer=https://auth.thermofisher.com/gs/webSdk/Api.aspx?apiKey={apiKey}&version=latest&build=17112&serviceName=apiService", ENDITEM, 
		"Url=/accounts.webSdkBootstrap?apiKey={apiKey}&pageURL="
		"https%3A%2F%2Fqa-identity.thermofisher.com%2Faccount-center%2Fproxy.html%3Fcontext%3D{context}%26client_id%3D{client_id}%26mode%3Dlo"
		"gin%26scope%3Dopenid%2Bprofile%2Bemail%2Btenant&sdk=js_latest&sdkBuild=17112&format=json", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
		LAST);

	web_url("sso.htm", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=17112", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t196.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=https://www.qa.thermofisher.com/favicon.ico", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
		"Url=../sdk.config.get?apiKey={ssoKey}&httpStatusCodes=true&ver=1742483880000", "Referer=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=17112", ENDITEM, 
		LAST);

	web_url("sso.htm_2", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=17112", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t197.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=../sdk.config.get?apiKey={ssoKey}&httpStatusCodes=true&ver=1742483880000", "Referer=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=17112", ENDITEM, 
		LAST);
   
    web_reg_find("Search=Body","SaveCount=txtChk","Text/IC=Sign In Identifier",LAST);
   

	web_url("signin-identifier.html", 
		"URL=https://qa-identity.thermofisher.com/account-center/signin-identifier.html?gig_client_id={client_id}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/account-center/proxy.html?context={context}&client_id={client_id}&mode=login&scope=openid+profile+email+tenant", 
		"Snapshot=t198.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=https://auth.thermofisher.com/sdk.config.get?apiKey={apiKey}&httpStatusCodes=true&ver=1742483880000", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
		"Url=scripts/tfSigninIdentifier-en-US-1742281383067.min.js", "Referer=https://qa-identity.thermofisher.com/account-center/signin-identifier.html?gig_client_id={client_id}", ENDITEM, 
		"Url=../identity/static/js/tfidentity/rpDetails.js", "Referer=https://qa-identity.thermofisher.com/account-center/signin-identifier.html?gig_client_id={client_id}", ENDITEM, 
		LAST);

	web_url("Api.aspx_2", 
		"URL=https://auth.thermofisher.com/gs/webSdk/Api.aspx?apiKey={apiKey}&version=latest&build=17112&serviceName=apiService", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t199.inf", 
		LAST);

	

	web_custom_request("urls", 
		"URL=https://qa-identity.thermofisher.com/api-gateway/identity-authorization/identity/auth-services/rp/urls/", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://qa-identity.thermofisher.com/account-center/signin-identifier.html?gig_client_id={client_id}", 
		"Snapshot=t202.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=https://www.qa.thermofisher.com/favicon.ico", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
		"Url=/identity/shared-static/images/icons/flags/us.gif", "Referer=https://qa-identity.thermofisher.com/account-center/signin-identifier.html?gig_client_id={client_id}", ENDITEM, 
		LAST);

	web_url("sso.htm_3", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=17112", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t203.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=../sdk.config.get?apiKey={ssoKey}&httpStatusCodes=true&ver=1742483880000", "Referer=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=17112", ENDITEM, 
		LAST);

	web_custom_request("rpDetails", 
		"URL=https://qa-identity.thermofisher.com/identity/account/api/validator/rpDetails", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://qa-identity.thermofisher.com/account-center/signin-identifier.html?gig_client_id={client_id}", 
		"Snapshot=t204.inf", 
		"Mode=HTML", 
		"EncType=application/json", 
		"Body={\"clientId\":\"{client_id}\",\"iso_code\":\"us\",\"lang_code\":\"en\",\"referral_url\":null}", 
		LAST);

	web_url("sso.htm_4", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=17112", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t205.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=../sdk.config.get?apiKey={ssoKey}&httpStatusCodes=true&ver=1742483880000", "Referer=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=17112", ENDITEM,
		LAST);
   
   if(atoi(lr_eval_string("{txtChk}"))==0){
		
    lr_end_transaction("03_ClickSignIn", LR_FAIL);
	lr_output_message("%s", lr_eval_string("03_ClickSignIn failed. UserName: {P_userName} ,Timestamp : {Timestamp}"));
	lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
		
	lr_end_transaction("03_ClickSignIn", LR_AUTO);
	
	lr_think_time(lr_get_attrib_double("TT"));


	/* useraname */
	/* next */
	
	web_add_auto_header("Sec-Fetch-Site", 		"same-origin");
	
	lr_start_transaction("04_EnterUsernameandClickNext");
	
	web_custom_request("findfederateduser", 
		"URL=https://qa-identity.thermofisher.com/api-gateway/identity-authorization/identity/fed/findfederateduser", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://qa-identity.thermofisher.com/account-center/signin-identifier.html", 
		"Snapshot=t27.inf", 
		"Mode=HTML", 
		"EncType=application/json", 
		"Body={\"username\":\"{P_userName}\"}", 
		LAST);


	web_revert_auto_header("Origin");
	web_add_auto_header("Sec-Fetch-Mode", 		"navigate");
	web_add_auto_header("Sec-Fetch-Dest", 		"document");
	web_add_header("Sec-Fetch-User", 		"?1");
	web_add_header("Upgrade-Insecure-Requests", 		"1");

	web_add_cookie("RT=\"z=1&dm=qa.thermofisher.com&si=37f9dfde-cc14-4cb8-a279-353a437fcd9b&ss=klq5sv9h&sl=2&tt=bfe&bcn=%2F%2F17d09919.akstat.io%2F&ld=c1x&nu=38099c8b67bd24bdbac54b67a4825440&cl=yu8&ul=yvb&hd=yx3\"; DOMAIN=qa-identity.thermofisher.com");

	web_url("signin.html", 
		"URL=https://qa-identity.thermofisher.com/account-center/signin.html", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/account-center/signin-identifier.html", 
		"Snapshot=t28.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=scripts/tfSignin-en-US-1613446768662.min.js", ENDITEM, 
		LAST);

	web_add_auto_header("Sec-Fetch-Site", 		"cross-site");
	web_add_auto_header("Sec-Fetch-Mode", 		"no-cors");
	web_add_auto_header("Sec-Fetch-Dest", 		"empty");
	web_add_header("Origin", 		"https://qa-identity.thermofisher.com");

	web_add_cookie("at_check=true; DOMAIN=auth.thermofisher.com");
	web_add_cookie("userType=internal; DOMAIN=auth.thermofisher.com");
	web_add_cookie("AMCVS_5B135A0C5370E6B40A490D44%40AdobeOrg=1; DOMAIN=auth.thermofisher.com");
	web_add_cookie("adcloud={%22_les_v%22:%22y%2Cthermofisher.com%2C1614579393%22}; DOMAIN=auth.thermofisher.com");
	web_add_cookie("AMCV_5B135A0C5370E6B40A490D44%40AdobeOrg=-408604571%7CMCIDTS%7C18688%7CMCMID%7C24015434127784847422512534986574036591%7CMCAID%7C301E3FDC51D3E824-400011AA3AEF5BC1%7CMCOPTOUT-1614584793s%7CNONE%7CMCAAMLH-1615182393%7C7%7CMCAAMB-1615182393%7Cj8Odv6LonN4r3an7LhD3WZrU1bUpAkFkkiY1ncBR96t2PTI%7CMCSYNCSOP%7C411-18695%7CvVersion%7C4.6.0; DOMAIN=auth.thermofisher.com");
	web_add_cookie("mbox=session#92861f61b197481ca0e9ff5d9628e480#1614579453|PC#92861f61b197481ca0e9ff5d9628e480.35_0#1677822394; DOMAIN=auth.thermofisher.com");
	web_add_cookie("s_tp=995; DOMAIN=auth.thermofisher.com");
	web_add_cookie("s_ppv=account%253Alogin%2C62%2C62%2C620; DOMAIN=auth.thermofisher.com");
	web_add_cookie("c31=account%20login; DOMAIN=auth.thermofisher.com");
	web_add_cookie("s_cc=true; DOMAIN=auth.thermofisher.com");
	web_add_cookie("s_sq=lifetech-thermofisher-qa%3D%2526c.%2526a.%2526activitymap.%2526page%253Daccount%25253Alogin%2526link%253DNext%2526region%253DThermofisher-two-step-login-username%2526pageIDType%253D1%2526.activitymap%2526.a%2526.c%2526pid%253Daccount%25253Alogin%2526pidt%253D1%2526oid%253Dfunction%252528%252529%25257Ba.validateFedUser%252528%252529%25257D%2526oidt%253D2%2526ot%253DSUBMIT; DOMAIN=auth.thermofisher.com");
	//web_add_cookie("cip_identifier={P_userName}@thermofisher.com; DOMAIN=auth.thermofisher.com");
	web_add_cookie("RT=\"z=1&dm=qa.thermofisher.com&si=37f9dfde-cc14-4cb8-a279-353a437fcd9b&ss=klq5sv9h&sl=2&tt=bfe&bcn=%2F%2F17d09919.akstat.io%2F\"; DOMAIN=qa-identity.thermofisher.com");
	web_add_auto_header("Sec-Fetch-Dest", 		"iframe");
	web_add_auto_header("Sec-Fetch-Mode", 		"navigate");
	web_add_auto_header("Sec-Fetch-Site", 		"same-site");
	web_add_auto_header("Upgrade-Insecure-Requests", 		"1");
	
	
//	web_reg_save_param("gmidVal", "LB=set-cookie: gmid=", "RB=; expires=", "Search=HEADERS",LAST);
//	web_reg_save_param("ucidVal", "LB=set-cookie: ucid=", "RB=; expires=", "Search=HEADERS",LAST);
	
	
	web_url("Api.aspx_3", 
		"URL=https://auth.thermofisher.com/gs/webSdk/Api.aspx?apiKey={apiKey}&version=latest&build=15936", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t30.inf", 
		"Mode=HTML", 
		EXTRARES, 
//		"Url=https://content-autofill.googleapis.com/v2/pages/ChRDaHJvbWUvODguMC40MzI0LjE4MhIXCXuntBNlbh6hEgUNJzlryhIFDc5BTHo=?alt=proto", "Referer=", ENDITEM, 
		"Url=/accounts.webSdkBootstrap?apiKey={apiKey}&pageURL=https%3A%2F%2Fqa-identity.thermofisher.com%2Faccount-center%2Fsignin.html&sdk=js_latest&sdkBuild=15936&format=json", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
//	    "Url=https://assets.adobedtm.com/launch-ENe956028acf6f4129a803968d774515c2-development.min.js", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
//		"Url=https://qa-identity.thermofisher.com/account-center/images/backarrow-1613446768662.png", "Referer=https://qa-identity.thermofisher.com/account-center/styles/signin-1613446768662.min.css", ENDITEM, 
//		"Url=https://qa-identity.thermofisher.com/account-center/images/view-on-1613446768662.svg", "Referer=https://qa-identity.thermofisher.com/account-center/styles/signin-1613446768662.min.css", ENDITEM,
		LAST);

	web_url("sso.htm_6", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=15936", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t31.inf", 
		"Mode=HTML", 
		LAST);

	web_revert_auto_header("Upgrade-Insecure-Requests");
	web_add_auto_header("Origin", 		"https://qa-identity.thermofisher.com");
	web_add_auto_header("Sec-Fetch-Dest", 		"empty");
	web_add_auto_header("Sec-Fetch-Mode", 		"cors");
	web_add_auto_header("Sec-Fetch-Site", 		"cross-site");



	web_add_auto_header("Sec-Fetch-Mode", 		"no-cors");
	web_add_cookie("adcloud={%22_les_v%22:%22y%2Cthermofisher.com%2C1614579422%22}; DOMAIN=auth.thermofisher.com");
	web_revert_auto_header("Origin");
	web_add_auto_header("Sec-Fetch-Mode",		"navigate");
	web_add_auto_header("Sec-Fetch-Dest", 		"iframe");
	web_add_auto_header("Sec-Fetch-Site", 		"same-site");
	web_add_header("Upgrade-Insecure-Requests", 		"1");

	web_url("sso.htm_7", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=15936", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t35.inf", 
		"Mode=HTML", 
		LAST);

	//web_add_cookie("cip_identifier={P_userName}@thermofisher.com; DOMAIN=somni.thermofisher.com");
	web_add_cookie("adcloud={%22_les_v%22:%22y%2Cthermofisher.com%2C1614579422%22}; DOMAIN=somni.thermofisher.com");
	web_add_cookie("mbox=session#92861f61b197481ca0e9ff5d9628e480#1614579453|PC#92861f61b197481ca0e9ff5d9628e480.35_0#1677822423; DOMAIN=somni.thermofisher.com");
	web_add_cookie("s_sq=%5B%5BB%5D%5D; DOMAIN=somni.thermofisher.com");
	web_add_cookie("RT=\"z=1&dm=qa.thermofisher.com&si=37f9dfde-cc14-4cb8-a279-353a437fcd9b&ss=klq5sv9h&sl=3&tt=bmx&bcn=%2F%2F17d09919.akstat.io%2F&ld=z8c\"; DOMAIN=qa-identity.thermofisher.com");
	web_add_cookie("adcloud={%22_les_v%22:%22y%2Cthermofisher.com%2C1614579422%22}; DOMAIN=qa-identity.thermofisher.com");
	web_add_cookie("mbox=session#92861f61b197481ca0e9ff5d9628e480#1614579453|PC#92861f61b197481ca0e9ff5d9628e480.35_0#1677822423; DOMAIN=qa-identity.thermofisher.com");
	web_add_cookie("s_sq=%5B%5BB%5D%5D; DOMAIN=qa-identity.thermofisher.com");
	web_add_auto_header("Sec-Fetch-Mode", 		"cors");
	web_add_auto_header("Sec-Fetch-Dest", 		"empty");
	web_add_header("Origin", 		"https://qa-identity.thermofisher.com");

		web_custom_request("urls_2", 
		"URL=https://qa-identity.thermofisher.com/api-gateway/identity-authorization/identity/auth-services/rp/urls/", 
		"Method=GET", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://qa-identity.thermofisher.com/account-center/signin.html", 
		"Snapshot=t160.inf", 
		"Mode=HTML", 
		LAST);




	
	if(atoi(lr_eval_string("{txtChk}"))==0){
		
    lr_end_transaction("04_EnterUsernameandClickNext", LR_FAIL);
	lr_output_message("%s", lr_eval_string("04_EnterUsernameandClickNext failed. UserName: {P_userName} ,Timestamp : {Timestamp}"));
	lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
		
	lr_end_transaction("04_EnterUsernameandClickNext", LR_AUTO);
	
	lr_think_time(lr_get_attrib_double("TT"));

	/* password */

	web_add_cookie("mbox=session#92861f61b197481ca0e9ff5d9628e480#1614579453|PC#92861f61b197481ca0e9ff5d9628e480.35_0#1677822423; DOMAIN=auth.thermofisher.com");
	web_add_cookie("s_sq="
		"lifetech-thermofisher-qa%3D%2526c.%2526a.%2526activitymap.%2526page%253Daccount%25253Alogin%2526link%253DSign%252520In%2526region%253Dgigya-login-form%2526pageIDType%253D1%2526.activitymap%2526.a%2526.c%2526pid%253Daccount%25253Alogin%2526pidt%253D1%2526oid%253Dfunction%252528%252529%25257Bp%25253Ddocument.getElementById%252528%252522username-field%252522%252529.value%25252C%252522%252522%25253D%25253Dp%252526%252526%252528o.location%25253D%252522signin-identifier.h%2526oidt%253D2%2526ot%253DSUBMIT"
		"; DOMAIN=auth.thermofisher.com");
	web_add_auto_header("Sec-Fetch-Mode", 		"navigate");
	web_add_auto_header("Sec-Fetch-Dest", 		"iframe");
	web_add_header("Upgrade-Insecure-Requests", 		"1");

    lr_start_transaction("05_EnterPasswordandSignIn");
    
	web_url("sso.htm_8", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=15936", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t37.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("Sec-Fetch-Mode", 		"cors");
	web_add_auto_header("Sec-Fetch-Dest", 		"empty");
	web_add_header("Origin", 		"https://qa-identity.thermofisher.com");
	
//	web_add_cookie("gmid={gmidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("ucid={ucidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("hasGmid=ver4; DOMAIN=auth.thermofisher.com");
	
	
	//st2.s.AcbH0UbSqA.aeIuZUjrUhbbG0NJ4GL4Iz55mFoBqTKeI3xSXWCWGXgDX4dK1Q_qAg00filknLB_p44CHOfdRseI8LyqCwZq48x5XfPuWiuJryscHCEieyY.dogfsRa6QeIOxuqp5xLpXldQTvIBSxBYNkRQte-u2BbF7CgY6gGdL6v_2Uv-dOR5y7DIFTYJJVZanlepZLovSg.sc3
	
	
	web_reg_save_param_ex("ParamName=logintoken","LB=\"login_token\": \"","RB=\",",SEARCH_FILTERS,"Scope=Body","IgnoreRedirections=No",LAST);
	
	web_reg_save_param_ex("ParamName=C_UID","LB=\"UID\": \"","RB=\",",SEARCH_FILTERS,"Scope=Body","IgnoreRedirections=No",LAST);

	
//	web_reg_save_param_ex("ParamName=signatureTimestamp","LB=\"signatureTimestamp\": \"","RB=\",\r",SEARCH_FILTERS,"Scope=Body","IgnoreRedirections=No",LAST);
//	 These corrlations are now captured from request "socialize.getUserInfo" down in code
//	web_reg_save_param_ex("ParamName=uidsig","LB=\"UIDSignature\": \"","RB=\",\r",SEARCH_FILTERS,"Scope=Body","IgnoreRedirections=No",LAST);

	web_submit_data("accounts.login", 
		"Action=https://auth.thermofisher.com/accounts.login", 
		"Method=POST", 
		"RecContentType=text/javascript", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t38.inf", 
		"Mode=HTML", 
		"EncodeAtSign=YES", 
		ITEMDATA, 
		"Name=loginID", "Value={P_userName}", ENDITEM, 
		"Name=password", "Value={P_password}", ENDITEM, 
		"Name=sessionExpiration", "Value=21600", ENDITEM, 
		"Name=targetEnv", "Value=jssdk", ENDITEM, 
		"Name=include", "Value=profile,data,emails,subscriptions,preferences,", ENDITEM, 
		"Name=includeUserInfo", "Value=true", ENDITEM, 
		"Name=loginMode", "Value=standard", ENDITEM, 
		"Name=lang", "Value=en", ENDITEM, 
		"Name=APIKey", "Value={apiKey}", ENDITEM, 
		"Name=source", "Value=showScreenSet", ENDITEM, 
		"Name=sdk", "Value=js_latest", ENDITEM, 
		"Name=authMode", "Value=cookie", ENDITEM, 
		"Name=pageURL", "Value=https://qa-identity.thermofisher.com/account-center/signin.html", ENDITEM, 
		"Name=sdkBuild", "Value=15936", ENDITEM, 
		"Name=format", "Value=json", ENDITEM, 
		EXTRARES, 
		"Url=https://cdns1.gigya.com/gs/i//accounts/bigLoader.gif", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
		LAST);

	web_add_cookie("glt_{apiKey}={logintoken}; DOMAIN=auth.thermofisher.com");
	web_add_cookie("glt_{apiKey}={logintoken}; DOMAIN=somni.thermofisher.com");
	web_add_auto_header("Sec-Fetch-Dest", 		"iframe");
	web_add_auto_header("Sec-Fetch-Mode", 		"navigate");
	web_add_auto_header("Upgrade-Insecure-Requests", 		"1");	
	
	web_url("sso.htm_9", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=15936", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t39.inf", 
		"Mode=HTML", 
		EXTRARES, 
		/*"Url=https://somni.thermofisher.com/b/ss/lifetech-thermofisher-qa/10/JS-2.20.0-LBQ1/s7135035339845?AQB=1&ndh=1&pf=1&callback=s_c_il[1].doPostbacks&et=1&t=1%2F2%2F2021%200%3A47%3A28%201%20300&d.&nsid=0&jsonv=1&.d&mid=24015434127784847422512534986574036591&aid=301E3FDC51D3E824-400011AA3AEF5BC1&aamlh=7&ce=UTF-8&pageName=account%3Alogin&g=https%3A%2F%2Fqa-identity.thermofisher.com%2Faccount-center%2Fsignin.html&server=qa-identity.thermofisher.com&events=event6&v1=account%3Alogin&c2="
		"https%3A%2F%2Fqa-identity.thermofisher.com%2Faccount-center%2Fsignin.html&v2=https%3A%2F%2Fqa-identity.thermofisher.com%2Faccount-center%2Fsignin.html&c3=account%20login&v3=account%20login&c4=24015434127784847422512534986574036591&c8=account%3Alogin&c10=thermo&c11=internal&c12=anonymous&v12=anonymous&v14=account%3Alogin&v15=thermo&c18=Mozilla%2F5.0%20%28Windows%20NT%206.3%3B%20Win64%3B%20x64%29%20AppleWebKit%2F537.36%20%28KHTML%2C%20like%20Gecko%29%20Chrome%2F88.0.4324.182%20Safari%2F537.36&c21=us%3Aen&c23="
		"en%7Caccount%3Alogin&v30=2021-03-01&v32=%28non-company%20visitor%29%3A%28non-company%20visitor%29%3A%28non-company%20visitor%29%3A%28non-company%20visitor%29%3A%28non-company%20visitor%29%3A%28non-company%20visitor%29%3Asmb%3A%28non-company%20visitor%29&c39=account%3Alogin&v63=account%20login&v73="
		"%28non-company%20visitor%29%3A%28non-company%20visitor%29%3A%28non-company%20visitor%29%3A52.204.73.115%3A%28non-company%20visitor%29%3A%28non-company%20visitor%29%3A%28non-company%20visitor%29%3A%28non-company%20visitor%29&v74=https%3A%2F%2Fqa-identity.thermofisher.com%2Faccount-center%2Fsignin&v76=account%3Alogin&pe=lnk_o&pev2=userLogin&c.&a.&activitymap.&page=account%3Alogin&link=Sign%20In&region=gigya-login-form&pageIDType=1&.activitymap&.a&.c&pid=account%3Alogin&pidt=1&oid="
		"function%28%29%7Bp%3Ddocument.getElementById%28%22username-field%22%29.value%2C%22%22%3D%3Dp%26%26%28o.location%3D%22signin-identifier.h&oidt=2&ot=SUBMIT&s=1366x768&c=24&j=1.6&v=N&k=Y&bw=1027&bh=620&mcorgid=5B135A0C5370E6B40A490D44%40AdobeOrg&lrt=19&AQE=1", "Referer=https://qa-identity.thermofisher.com/", ENDITEM,*/ 
		LAST);

	web_add_cookie("glt_{apiKey}={logintoken}; DOMAIN=qa-identity.thermofisher.com");
	web_add_cookie("RT=\"z=1&dm=qa.thermofisher.com&si=37f9dfde-cc14-4cb8-a279-353a437fcd9b&ss=klq5sv9h&sl=3&tt=bmx&bcn=%2F%2F17d09919.akstat.io%2F&ld=z8c&ul=1joq\"; DOMAIN=qa-identity.thermofisher.com");
	web_add_auto_header("Sec-Fetch-Site", 		"same-origin");
	web_add_auto_header("Sec-Fetch-Dest", 		"document");
	web_add_header("Sec-Fetch-User", 		"?1");		

	web_url("proxy.html", 
		"URL=https://qa-identity.thermofisher.com/account-center/proxy.html?mode=afterLogin", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/account-center/signin.html", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		LAST);


	web_add_cookie("gig_loginToken_{ssoKey}={logintoken}; DOMAIN=auth.thermofisher.com");
	web_add_cookie("gig_loginToken_{ssoKey}_exp=1614599247932; DOMAIN=auth.thermofisher.com");
	web_add_cookie("gig_loginToken_{ssoKey}_visited=%2C{apiKey}; DOMAIN=auth.thermofisher.com");
	web_add_cookie("s_sq=%5B%5BB%5D%5D; DOMAIN=auth.thermofisher.com");
	web_add_auto_header("Sec-Fetch-Dest",		"iframe");
	web_add_auto_header("Sec-Fetch-Mode", 		"navigate");
	web_add_auto_header("Sec-Fetch-Site", 		"same-site");
	web_add_auto_header("Upgrade-Insecure-Requests", 		"1");

//    web_add_cookie("gmid={gmidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("ucid={ucidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("hasGmid=ver4; DOMAIN=auth.thermofisher.com");
	
	web_url("Api.aspx_4", 
		"URL=https://auth.thermofisher.com/gs/webSdk/Api.aspx?apiKey={apiKey}&version=latest&build=15936", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t42.inf", 
		"Mode=HTML", 
		LAST);
					

	web_url("sso.htm_10", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=15936", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t43.inf", 
		"Mode=HTML",
		LAST);
	
	
	/***************************Missing request********************/
	
//	web_add_cookie("gmid={gmidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("ucid={ucidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("hasGmid=ver4; DOMAIN=auth.thermofisher.com");
	
	web_reg_save_param_ex("ParamName=uidsig","LB=\"UIDSignature\": \"","RB=\",",SEARCH_FILTERS,"Scope=BODY",LAST);
	web_reg_save_param_ex("ParamName=signatureTimestamp","LB=\"signatureTimestamp\": \"","RB=\",",SEARCH_FILTERS,"Scope=BODY",LAST);

	web_reg_find("Search=Body","SaveCount=Textcheck1","Text=\"isLoggedIn\": true",LAST);
	
	web_submit_data("socialize.getUserInfo", 
		"Action=https://auth.thermofisher.com/socialize.getUserInfo", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/javascript", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t270.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=enabledProviders", "Value=*", ENDITEM, 
		"Name=include", "Value=profile,data,emails,subscriptions,preferences,id_token,missing-required-fields", ENDITEM, 
		"Name=APIKey", "Value={apiKey}", ENDITEM, 
		"Name=sdk", "Value=js_latest", ENDITEM, 
		"Name=login_token", "Value={logintoken}", ENDITEM, 
		"Name=authMode", "Value=cookie", ENDITEM, 
		"Name=pageURL", "Value=https://qa-identity.thermofisher.com/account-center/proxy.html?mode=afterLogin", ENDITEM, 
		"Name=sdkBuild", "Value=15936", ENDITEM, 
		"Name=format", "Value=json", ENDITEM, 
		LAST);

	web_add_cookie("RT=\"z=1&dm=qa.thermofisher.com&si=37f9dfde-cc14-4cb8-a279-353a437fcd9b&ss=klq5sv9h&sl=4&tt=bmx&bcn=%2F%2F17d09919.akstat.io%2F&obo=1&ld=1k1f&r=e4c4ca1ae0c9b8cf0b37d0ae6c8f312a&ul=1k1g\"; DOMAIN=qa-identity.thermofisher.com");
	web_add_auto_header("Sec-Fetch-Site", 		"same-origin");
	web_add_auto_header("Sec-Fetch-Dest", 		"document");
	
	
	web_convert_param("uidsig_URL2","SourceString={uidsig}","SourceEncoding=HTML","TargetEncoding=URL",LAST);
	
	web_reg_save_param_ex("ParamName=sig_1","LB=sig=","RB=\r\n",SEARCH_FILTERS,"Scope=Headers","IgnoreRedirections=No","RequestUrl=*/consent*",LAST);


//	web_url("consent", 
//		"URL=https://qa-identity.thermofisher.com/api-gateway/identity-authorization/identity/auth/consent?context={context}&clientID={client_id}&scope=openid%2Bopenid%2Bemail%2Bprofile&prompt=consent&UID={C_UID}&UIDSignature={uidsig_URL2}&signatureTimestamp={signatureTimestamp}", 
//		"Resource=0", 
//		"RecContentType=text/html", 
//		"Referer=https://qa-identity.thermofisher.com/account-center/proxy.html?mode=afterLogin", 
//		"Snapshot=t44.inf", 
//		"Mode=HTML", 
//		LAST);
	
	/***************************Consent request URL modified********************/
	
	web_url("consent", 
		"URL=https://qa-identity.thermofisher.com/api-gateway/identity-authorization/identity/auth/consent?context={context}&clientID={client_id}&scope=openid%2Bprofile%2Bemail%2Btenant&UID={C_UID}&UIDSignature={uidsig_URL2}&signatureTimestamp={signatureTimestamp}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/account-center/proxy.html?mode=afterLogin", 
		"Snapshot=t280.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=https://auth.thermofisher.com/sdk.config.get?apiKey={apiKey}&httpStatusCodes=true", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
		LAST);

	web_add_auto_header("Sec-Fetch-Site", 		"same-site");
	web_add_auto_header("Sec-Fetch-Dest", 		"iframe");
	
//	web_add_cookie("gmid={gmidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("ucid={ucidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("hasGmid=ver4; DOMAIN=auth.thermofisher.com");

	web_url("Api.aspx_5", 
		"URL=https://auth.thermofisher.com/gs/webSdk/Api.aspx?apiKey={apiKey}&version=latest&build=15936", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t45.inf", 
		"Mode=HTML", 
		LAST);
	
	/*****************New Code Starts here **************/
	
	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Accept", 
		"*/*");

	web_add_header("Access-Control-Allow-Headers", 
		"*");

	web_add_header("Access-Control-Allow-Methods", 
		"GET");

	web_add_header("Access-Control-Allow-Origin", 
		"*");

	web_add_header("Content-Type", 
		"text/javascript; charset=utf-8");

	web_add_auto_header("Sec-Fetch-Dest", 
		"empty");

	web_add_auto_header("Sec-Fetch-Mode", 
		"cors");

	web_custom_request("entitlements", 
		"URL=https://qa-identity.thermofisher.com/api-gateway/identity-authorization/identity/auth/entitlements/?uid={C_UID}", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://qa-identity.thermofisher.com/identity/auth-ui/tenant/index.html?mode=afterConsent&consent="
		"%7B%22context%22%3A%22{context}%22%2C%22scope%22%3A%22openid+profile+email+"
		"tenant%22%2C%22clientID%22%3A%22{client_id}%22%2C%22consent%22%3Atrue%2C%22uid%22%3A%22{C_UID}%22%2C%22UID%22%3A%22{C_UID}%22%7D&sig={sig_1}&uid={C_UID}", 
		"Snapshot=t300.inf", 
		"Mode=HTML", 
		"EncType=text/javascript; charset=utf-8", 
		LAST);

	web_add_auto_header("Sec-Fetch-Site", 
		"same-site");

	web_add_header("Origin", 
		"https://qa-identity.thermofisher.com");
	
//	web_add_cookie("gmid={gmidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("ucid={ucidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("hasGmid=ver4; DOMAIN=auth.thermofisher.com");
	
	web_reg_find("Search=Body","SaveCount=Textcheck","Text/IC=statusCode\": 200",LAST);

	web_submit_data("accounts.getAccountInfo", 
		"Action=https://auth.thermofisher.com/accounts.getAccountInfo", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/javascript", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t310.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=include", "Value=profile,", ENDITEM, 
		"Name=lang", "Value=en", ENDITEM, 
		"Name=APIKey", "Value={apiKey}", ENDITEM, 
		"Name=sdk", "Value=js_latest", ENDITEM, 
		"Name=login_token", "Value={logintoken}", ENDITEM, 
		"Name=authMode", "Value=cookie", ENDITEM, 
		"Name=pageURL", "Value=https://qa-identity.thermofisher.com/identity/auth-ui/tenant/index.html?mode=afterConsent&consent="
		"%7B%22context%22%3A%22{context}%22%2C%22scope%22%3A%22openid+profile+email+"
		"tenant%22%2C%22clientID%22%3A%22{client_id}%22%2C%22consent%22%3Atrue%2C%22uid%22%3A%22{C_UID}%22%2C%22UID%22%3A%22{C_UID}%22%7D&sig={sig_1}&uid={C_UID}", ENDITEM, 
		"Name=sdkBuild", "Value=15936", ENDITEM, 
		"Name=format", "Value=json", ENDITEM, 
		LAST);
	
	if(atoi(lr_eval_string("{Textcheck}"))==0){
		
    lr_end_transaction("05_EnterPasswordandSignIn", LR_FAIL);
	lr_output_message("%s", lr_eval_string("05_EnterPasswordandSignIn failed. UserName: {P_userName} ,Timestamp : {Timestamp}"));
	lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
		
	lr_end_transaction("05_EnterPasswordandSignIn", LR_AUTO);
	
	lr_think_time(lr_get_attrib_double("TT"));

	/* Select Tenant */

	web_add_header("Access-Control-Allow-Headers", 
		"*");

	web_add_header("Access-Control-Allow-Methods", 
		"GET");

	web_add_header("Access-Control-Allow-Origin", 
		"*");

	web_add_header("Content-Type", 
		"text/javascript; charset=utf-8");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");
	
	
	
	lr_start_transaction("06_SelectTenant");

	web_custom_request("continue", 
		"URL=https://qa-identity.thermofisher.com/api-gateway/identity-authorization/identity/auth/consent/continue/?uid={C_UID}&alias={P_TenantName}&id={P_TenantID}&org=DSBU+Testing&env={Env}&mode=afterConsent&consent="
		"%7B%22context%22%3A%22{context}%22%2C%22scope%22%3A%22openid+profile+email+"
		"tenant%22%2C%22clientID%22%3A%22{client_id}%22%2C%22consent%22%3Atrue%2C%22uid%22%3A%22{C_UID}%22%2C%22UID%22%3A%22{C_UID}%22%7D&sig={sig_1}", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://qa-identity.thermofisher.com/identity/auth-ui/tenant/index.html?mode=afterConsent&consent="
		"%7B%22context%22%3A%22{context}%22%2C%22scope%22%3A%22openid+profile+email+"
		"tenant%22%2C%22clientID%22%3A%22{client_id}%22%2C%22consent%22%3Atrue%2C%22uid%22%3A%22{C_UID}%22%2C%22UID%22%3A%22{C_UID}%22%7D&sig={sig_1}&uid={C_UID}", 
		"Snapshot=t320.inf", 
		"Mode=HTML", 
		"EncType=text/javascript; charset=utf-8", 
		LAST);

	web_add_auto_header("Accept", 
		"text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_url("proxy.html_2", 
		"URL=https://qa-identity.thermofisher.com/account-center/proxy.html?mode=afterConsent&consent="
		"%7B%22context%22%3A%22{context}%22%2C%22scope%22%3A%22openid+profile+email+"
		"tenant%22%2C%22clientID%22%3A%22{client_id}%22%2C%22consent%22%3Atrue%2C%22uid%22%3A%22{C_UID}%22%2C%22UID%22%3A%22{C_UID}%22%7D&sig={sig_1}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/identity/auth-ui/tenant/index.html?mode=afterConsent&consent="
		"%7B%22context%22%3A%22{context}%22%2C%22scope%22%3A%22openid+profile+email+"
		"tenant%22%2C%22clientID%22%3A%22{client_id}%22%2C%22consent%22%3Atrue%2C%22uid%22%3A%22{C_UID}%22%2C%22UID%22%3A%22{C_UID}%22%7D&sig={sig_1}&uid={C_UID}", 
		"Snapshot=t330.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=https://auth.thermofisher.com/js/gigya.oidc.js?apiKey={apiKey}", "Referer=https://qa-identity.thermofisher.com/", ENDITEM, 
		LAST);

	web_add_auto_header("Sec-Fetch-Site", 
		"same-site");

	web_add_auto_header("Sec-Fetch-Dest", 
		"iframe");

	//web_revert_auto_header("Upgrade-Insecure-Requests");
	
//	web_add_cookie("gmid={gmidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("ucid={ucidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("hasGmid=ver4; DOMAIN=auth.thermofisher.com");

	web_url("Api.aspx_6", 
		"URL=https://auth.thermofisher.com/gs/webSdk/Api.aspx?apiKey={apiKey}&version=latest&build=15936&serviceName=apiService", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t340.inf", 
		"Mode=HTML", 
		 LAST);
	
	web_url("sso.htm_17", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=16404", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t2470.inf", 
		"Mode=HTML", 
		LAST);

	web_url("sso.htm_18", 
		"URL=https://auth.thermofisher.com/gs/sso.htm?APIKey={ssoKey}&ssoSegment=&version=latest&build=16404", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t2480.inf", 
		"Mode=HTML", 
		LAST);

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

//	web_add_header("Upgrade-Insecure-Requests", 
//		"1");
	
	
//	web_add_cookie("gmid={gmidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("ucid={ucidVal}; DOMAIN=auth.thermofisher.com");
//	web_add_cookie("hasGmid=ver4; DOMAIN=auth.thermofisher.com");
	
	web_reg_save_param_ex("ParamName=c_platform_session","LB/IC=Set-Cookie: platform_session=","RB=;",SEARCH_FILTERS,LAST);
		
	//web_reg_save_param_ex("ParamName=c_platform_session_2","LB/IC=Set-Cookie: platform_session_2=","RB=;",SEARCH_FILTERS,LAST);
	
	web_reg_save_param_ex("ParamName=c_authToken","LB=code=","RB=&",SEARCH_FILTERS,"Scope=Headers","IgnoreRedirections=No",LAST);
	
	web_reg_find("Search=Body","SaveCount=Textcheck2","Text/IC= <title>DsbuPlatformUserhome</title>",LAST);

	
	web_url("continue_2", 
		"URL=https://auth.thermofisher.com/oidc/op/v1.0/{apiKey}/authorize/continue?context={context}&login_token="
		"{logintoken}&consent="
		"%7B%22context%22%3A%22{context}%22%2C%22scope%22%3A%22openid%20profile%20email%20tenant%22%2C%22clientID%22%3A%22{client_id}%22%2C%2"
		"2consent%22%3Atrue%2C%22uid%22%3A%22{C_UID}%22%2C%22UID%22%3A%22{C_UID}%22%7D&sig={sig_1}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=https://qa-identity.thermofisher.com/", 
		"Snapshot=t350.inf", 
		"Mode=HTML", 
		LAST);
	
	
	
	
	web_custom_request("getNotificationsList", 
		"URL=https://api.{P_Envname}.dsbu.cloud/nm/nmsvc/api/user/v5/notifications/getNotificationsList", 
		"Method=OPTIONS", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t360.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_save_param_ex("ParamName=c_etag","LB/IC=Etag: ","RB=\"\r\n",SEARCH_FILTERS,LAST);

	web_reg_find("Search=Body","SaveCount=Textcheck","Text/IC=Sign Out",LAST);

	web_url("v2_2", 
		"URL=https://api.{P_Envname}.dsbu.cloud/platformheader/headerdata/v2", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=https://userhome.{P_Envname}.dsbu.cloud/", 
		"Snapshot=t370.inf", 
		"Mode=HTML", 
		LAST);
	
	if(atoi(lr_eval_string("{Textcheck}"))==0)
	{	
    lr_end_transaction("06_SelectTenant",LR_FAIL);
	lr_output_message("%s", lr_eval_string("06_SelectTenant failed . UserName: {P_userName} ,Timestamp : {Timestamp}"));
	lr_exit(LR_EXIT_ITERATION_AND_CONTINUE, LR_AUTO);
	} 
	lr_end_transaction("06_SelectTenant",LR_PASS);		
	
	lr_think_time(lr_get_attrib_double("TT"));
	
	/************************** New Code Ends Here*****************************/
	
	

	
	
	

	return 0;
}
