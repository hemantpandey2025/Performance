int InitializeTestUserSettings()
    {                
        lr_whoami(&givuser_id, &vuser_group, &scid);
        lr_save_string((char *)strlwr(xURL),"URL");   
        lr_save_string(lr_get_attrib_string("Iterationcount"),"Iterationcount"); 
       	            
        if (givuser_id != -1)//If testing from controller, read parameters from attributes of Run-Time-Settings and over-write default values
            {    
               	lr_save_string(lr_get_attrib_string("URL"),"URL");                            
                lr_save_string(lr_get_attrib_string("Iterationcount"),"Iterationcount"); 
                
                targetedIterationsPerUserPerHour = atoi(lr_eval_string("{Iterationcount}"));
            }  

        return 0;
    }
    
//Calculate dynamic pacing to achieve targeted iteration per hour
void DynamicPacing()
    {
        if((atoi(lr_eval_string("{IterationNumber}"))!=1) && (givuser_id != -1)) //IterationNumber to read vUser iteration during run-time
            {
                actualIterationDuration = lr_end_timer(timer); //lr_output_message("actualIterationDuration: %f", actualIterationDuration);
                actualWaitDuration = 0;
                if (atoi(lr_eval_string("{expectedIterationDuration}"))>actualIterationDuration)
                    {
                        timer = lr_start_timer();
                        lr_think_time(atoi(lr_eval_string("{expectedIterationDuration}"))-actualIterationDuration);
                        actualWaitDuration = lr_end_timer(timer);
                    }
                lr_set_transaction(vuser_group, actualIterationDuration + actualWaitDuration,LR_PASS);
                timer = lr_start_timer();
            }
         else timer = lr_start_timer();
    }
    
int LGNamingCountryCode()
	{
		if (stricmp(lr_eval_string("{lgname}"), "awse3-10wpca01p")==0 || stricmp(lr_eval_string("{lgname}"), "awse3-10wpca02p")==0 || stricmp(lr_eval_string("{lgname}"), "ukpai-hppc-p1")==0 || stricmp(lr_eval_string("{lgname}"), "ukpai-hppc-p2")==0)
			{
				lr_save_string("UK", "LGCountry");
			}
		else if (stricmp(lr_eval_string("{lgname}"), "cnshf-pca01")==0 || stricmp(lr_eval_string("{lgname}"), "cnshf-pca02")==0)
			{
				lr_save_string("CN", "LGCountry");
			}
		else
			{
				lr_save_string("US", "LGCountry");
			}
		
		//lr_output_message("%s", lr_eval_string("Actual LG Name is {lgname}, Load Generator Output Name is {LGCountry}"));
		
		return 0;
	}