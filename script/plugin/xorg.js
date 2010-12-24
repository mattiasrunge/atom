
function Xorg_SendKey(key_name)
{
	if (arguments.length < 1)
	{
		Log("\033[31;1mNot enough parameters given.\033[0m\n");
		return false;
	}
	
	var keycode = Storage_GetParameter("Xorg_Keymap", key_name);
	
	if (XorgExport_SendKey(keycode))
        {
		Log("\033[32;Successfully sent code \"" + key_name + "\" (" + keycode + ").\033[0m\n");
		return true;
	}

	Log("\033[31;1mFailed to send code \"" + key_name + "\" (" + keycode + ").\033[0m\n");
	return false;
}
Console_RegisterCommand(Xorg_SendKey, function(args) { return Console_StandardAutocomplete(args, get_keys(torage_GetParameters("Xorg_Keymap"))); });
