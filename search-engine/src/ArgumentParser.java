import java.util.HashMap;
/**
 * Parses and stores an array of argument into flag, value pairs for easy access
 * later. Useful to parse command-line arguments.
 */
public class ArgumentParser
{

	/**
	 * Stores parsed flag, value pairs.
	 */
	private final HashMap<String, String> argumentMap;

	/**
	 * Creates a new and empty argument parser.
	 */
	public ArgumentParser()
	{
		argumentMap = new HashMap<String, String>();
	}

	/**
	 * Creates a new argument parser and immediately parses the passed
	 * arguments.
	 * 
	 * @param args
	 *            arguments to parse into flag, value pairs
	 * @see #parseArguments(String[])
	 */
	public ArgumentParser(String[] args)
	{
		this();
		parseArguments(args);
	}

	/**
	 * Parses the array of arguments into flag, value pairs. If an argument is a
	 * flag, tests whether the next argument is a value. If it is a value, then
	 * stores the flag, value pair. Otherwise, it stores the flag with no value.
	 * If the flag appears multiple times with different values, only the last
	 * value will be kept. Values without an associated flag are ignored.
	 * 
	 * @param args
	 *            arguments to parse into flag, value pairs
	 * @see #isFlag(String)
	 * @see #isValue(String)
	 */
	public void parseArguments(String[] args)
	{
		int i = 0;
		while(i < args.length)
		{
			String arg = args[i];
			if(isFlag(arg))
			{
				argumentMap.put(arg, "");
				if(i + 1 < args.length)
				{
					String arg2 = args[i + 1];
					if(isValue(arg2))
					{
						argumentMap.put(arg, arg2);
					}
				}
			}
			i++;
		}
	}

	/**
	 * Tests whether the argument is a valid flag, i.e. it is not null, and
	 * after trimming it starts with a dash "-" character followed by at least 1
	 * character.
	 * 
	 * @param arg
	 *            argument to test
	 * @return {@code true} if the argument is a valid flag
	 */
	public static boolean isFlag(String arg)
	{
		if(arg.startsWith("-"))
		{
			if(1 >= arg.length())
				return false;
			char x = arg.charAt(1);
			if(x == ' ')
				return false;
			return true;
		}
		return false;
	}

	/**
	 * Tests whether the argument is a valid value, i.e. it is not null, does
	 * not start with a dash "-" character, and is not empty after trimming.
	 * 
	 * @param arg
	 *            argument to test
	 * @return {@code true} if the argument is a valid value
	 */
	public static boolean isValue(String arg)
	{
		if(!arg.startsWith("-"))
		{
			if(arg.isEmpty() || arg.matches("\\s"))
				return false;
			return true;
		}
		return false;
	}

	/**
	 * Returns the number of flags stored.
	 * 
	 * @return number of flags
	 */
	public int numFlags()
	{
		return argumentMap.size();
	}

	/**
	 * Checks if the flag exists.
	 * 
	 * @param flag
	 *            flag to check for
	 * @return {@code true} if flag exists
	 */
	public boolean hasFlag(String flag)
	{
		if(argumentMap.get(flag)!=null)
			return true;
		return false;
	}

	/**
	 * Checks if the flag exists and has a non-null value.
	 * 
	 * @param flag
	 *            flag whose associated value is to be checked
	 * @return {@code true} if the flag exists and has a non-null value
	 */
	public boolean hasValue(String flag)
	{
		if(argumentMap.containsKey(flag))
		{
			if(argumentMap.get(flag) == "")
				return false;
			return true;
		}
		if(argumentMap.get(flag)!= null)
			return true;
		return false;
	}

	/**
	 * Returns the value associated with the specified flag. May be {@code null}
	 * if a {@code null} value was stored or if the flag does not exist.
	 * 
	 * @param flag
	 *            flag whose associated value is to be returned
	 * @return value associated with the flag or {@code null} if the flag does
	 *         not exist
	 */
	public String getValue(String flag)
	{
		if(argumentMap.get(flag)!="")
			return argumentMap.get(flag);
		return null;
	}

	/**
	 * Returns the value for a flag. If the flag is missing or the value is
	 * {@code null}, returns the default value instead.
	 * 
	 * @param flag
	 *            flag whose associated value is to be returned
	 * @param defaultValue
	 *            the default mapping of the flag
	 * @return value of flag or {@code defaultValue} if the flag is missing or
	 *         the value is {@code null}
	 */
	public String getValue(String flag, String defaultValue)
	{
		if(argumentMap.containsKey(flag))
		{
			if(argumentMap.get(flag) != "")
				return argumentMap.get(flag);
			else
				return defaultValue;
		}
		else
			return defaultValue;
	}

	/**
	 * Returns the value for a flag as an integer. If the flag or value is
	 * missing or if the value cannot be converted to an integer, returns the
	 * default value instead.
	 * 
	 * @param flag
	 *            flag whose associated value is to be returned
	 * @param defaultValue
	 *            the default mapping of the flag
	 * @return value of flag as an integer or {@code defaultValue} if the value
	 *         cannot be returned as an integer
	 */
	public int getValue(String flag, int defaultValue)
	{
		if(!argumentMap.containsKey(flag))
		{
			return defaultValue;
		}
		String y = argumentMap.get(flag);
		if(y.isEmpty() || y.matches("\\s") || y == null)
			return defaultValue;
		try
		{
			int x = Integer.parseInt(argumentMap.get(flag));
			return x;
		}
		catch (NumberFormatException e)
		{
			System.err.println("Invalid number format. Setting to default of: " + defaultValue);
			return defaultValue;
		}

	}

	@Override
	public String toString()
	{
		return argumentMap.toString();
	}
}
