function onCreate()
	callGMFunction(getGMFunction("show_message"), "Pressed: " .. callGMFunction(getGMFunction("show_message_ext"), "Hai", "1", "2", "3"))
end


