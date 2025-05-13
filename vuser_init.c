vuser_init()
{
	InitializeTestUserSettings();
	
	if (givuser_id != -1)//If testing from controller, read parameters from attributes of Run-Time-Settings and over-write default values
    	{ 
			lr_save_int(3600/targetedIterationsPerUserPerHour,"expectedIterationDuration");
		}
	
	web_set_max_html_param_len("999999");
	
	web_set_sockets_option("SSL_VERSION", "AUTO");
	
	/******Recent Updated: 14 May Month 2025 Save *******/
	
	return 0;
}
