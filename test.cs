/* 
 * test.cs
 * 
 * Copyright (C) Tom Spink 2011 <tspink@gmail.com>
 * All Rights Reserved
 */
using System;

namespace Test
{
	public class TestClass
	{
		private static int calls;
		private int count;
		
		public TestClass()
		{
			Console.WriteLine("The default constructor.");
		}
		
		public TestClass(int start)
		{
			count = start;
			Console.WriteLine("The parameterised constructor, starting at {0}", start);
		}
		
		public void TestMethod()
		{
			Console.WriteLine("This is the TestMethod(), called {0} times.", ++count);
		}
		
		public void TestMethod2(string name)
		{
			Console.WriteLine("This is the TestMethod2(), saying hello to {0}", name);
		}
		
		public static void TestStaticMethod()
		{
			Console.WriteLine("This is the static TestStaticMethod(), called {0} times.", ++calls);
		}
		
		public static int TestStaticMethod2()
		{
			int retval = 12345;
			Console.WriteLine("This is the static TestStaticMethod2(), about to return {0}.", retval);
			return retval;
		}
		
		public void TestMethod3()
		{
			throw new Exception("A test exception!");
		}
	}
}
