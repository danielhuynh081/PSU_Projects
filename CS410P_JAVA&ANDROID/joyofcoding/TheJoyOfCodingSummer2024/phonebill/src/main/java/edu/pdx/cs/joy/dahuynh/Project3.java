package edu.pdx.cs.joy.dahuynh;


import edu.pdx.cs.joy.ParserException;

import java.io.*;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
/**
 * The main class for the Phone Bill Project
 */
public class Project3 {
  public Project3(){

  }
  public static void main(String[] args) {

    //check for option only commands
    if (args.length == 1) {
      if (args[0].equalsIgnoreCase("-readme")) {
        printReadme();
        return;
      }
      if (args[0].equalsIgnoreCase("-print")) {
        System.err.println("There are no phone calls in the bill");
        return;
      }
      if (args[0].equalsIgnoreCase("-textfile")) {
        System.err.println("There are no phone calls in the bill");
        return;
      }
      System.err.println("Error: Insufficient arguments, Run the script with -README for more help");
    }
    //textdumper and parser


    //Command Line Error Checking
    boolean isValid = checkArguments(args);

    //Create PhoneCall and PhoneBill Objects Once Passes Error Testing
    if (isValid) {
      //Caller & Callee
      String caller = args[args.length - 8];
      String callee = args[args.length - 7];

//begin time info
      String beginDate = args[args.length - 6];
      String beginTime = args[args.length - 5];
      String beginAmPm = args[args.length - 4].toUpperCase();
      //end time info
      String endDate = args[args.length - 3];
      String endTime = args[args.length - 2];
      String endAmPm = args[args.length - 1].toUpperCase();



      LocalDateTime begininfostring = parsetime(beginDate, beginTime, beginAmPm);
      LocalDateTime endinfostring = parsetime(endDate, endTime, endAmPm);
      if(begininfostring.isAfter(endinfostring)) {
        System.err.println("Error: Begin time is after end time");
        return;
      }
      else if((begininfostring.isEqual(endinfostring))){
        System.err.println("Error: Begin time is equal to end time");
        return;
      }


      PhoneCall call = new PhoneCall(caller, callee, begininfostring, endinfostring);
      PhoneBill bill = new PhoneBill(args[args.length - 9]);

      bill.addPhoneCall(call);
      /*System.out.println("\nAdded Extra calls to show sorting requirement\n");
      bill.addPhoneCall(tester);
      bill.addPhoneCall(tester2);*/


      bill.sortPhoneCalls();

      System.out.println("\nPhone call added\n");
      //Display PhoneBill using flags -print or -readme

      //one argument
      if (args.length == 10) {
        if (args[0].equalsIgnoreCase("-readme")) {
          printReadme();
          return;
        }
        if (args[0].equalsIgnoreCase("-print")) {
          System.out.println("\nNewest Call\n");
          bill.printPhone();
          return;
        }
        if (args[0].equalsIgnoreCase("-textfile") || args[0].equalsIgnoreCase("-pretty")) {
          if (args[0].equalsIgnoreCase("-textfile")) {
            System.out.println("\n Needs a textfile after it\n");
          }
          if (args[0].equalsIgnoreCase("-pretty")) {
            System.out.println("\n Needs a textfile or - after it\n");
          }
        } else {
          System.err.println("\nInvalid option, use -README option for more help\n");
        }

      }
      //2 arguments
      if (args.length == 11) {
        if (args[0].equalsIgnoreCase("-readme") || args[1].equalsIgnoreCase("-readme")) {
          printReadme();
        }
        if (args[0].equalsIgnoreCase("-print") || args[1].equalsIgnoreCase("-print")) {
          System.out.println("\nNewest Call\n");
          bill.printPhone();
        }
        if (args[0].equalsIgnoreCase("-textfile")) {
          File fileinput = new File(args[1]);
          if (fileinput.exists() && !fileinput.isDirectory()) {
            try {
              FileReader fileReader = new FileReader(fileinput);

              TextParser parser = new TextParser(fileReader);

              bill = parser.parse();
	      bill.addPhoneCall(call);
	      bill.sortPhoneCalls();
              System.out.println(fileinput.toString() + " Parsed into new bill object.\n\nPrinting newly parsed bill object.");
              bill.printPhone();
            } catch (FileNotFoundException e) {
              throw new RuntimeException(e);
            } catch (ParserException e) {
              throw new RuntimeException(e);
            }
          } else {
            System.out.println("this file doesnt already exist, no parsing can be done");
          }
          try{
            FileWriter fileWriter = new FileWriter(fileinput);
            TextDumper dumper = new TextDumper(fileWriter);
            System.out.println("DUMPING");
            dumper.dump(bill);

          } catch (FileNotFoundException e) {
            System.err.println("File not found, cannot parse: " + fileinput.toString());
          } //catch (ParserException e) {
          //System.err.println("Error parsing phone bill: " + e.getMessage());
          catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }
        }
        if (args[0].equalsIgnoreCase("-pretty")) {
          File fileinput = new File(args[1]);

          try {
            FileWriter fileWriter = new FileWriter(fileinput);
            PrettyPrinter pretty = new PrettyPrinter(fileWriter);
            if (args[1].equalsIgnoreCase("-")) {
              System.out.println("STDOUT Pretty Print\n");
              pretty.prettyprint(bill);
            } else {

              pretty.prettyprint(bill);
            }

          } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }
        }
        if(!args[0].equalsIgnoreCase("-print") && !args[0].equalsIgnoreCase("-readme") && !args[0].equalsIgnoreCase("-textfile") && !args[0].equalsIgnoreCase("-pretty")){
          System.err.println(args[0] + " has to be a valid option");
        }
        if(!args[1].equalsIgnoreCase("-print") && !args[1].equalsIgnoreCase("-readme")){
          if(args[0].equalsIgnoreCase("-textfile") ||args[0].equalsIgnoreCase("-pretty")){
            return;
          }
          System.err.println(args[1] + " has to be a valid option");
        }

        return;
      }
      //3 arguments
      if (args.length == 12) {
        if (args[0].equalsIgnoreCase("-readme") || args[1].equalsIgnoreCase("-readme") || args[2].equalsIgnoreCase("-readme")) {
          printReadme();
        }
        if (args[0].equalsIgnoreCase("-print") || args[1].equalsIgnoreCase("-print") || args[2].equalsIgnoreCase("-print")) {
          System.out.println("\nNewest Call\n");
          bill.printPhone();
        }
        if (args[0].equalsIgnoreCase("-textfile") || args[1].equalsIgnoreCase("-textfile")) {
          File fileinput = null;
          if (args[0].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[1]);
          }
          if (args[1].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[2]);
          }

          if (fileinput.exists() && !fileinput.isDirectory()) {
            try {
              FileReader fileReader = new FileReader(fileinput);

              TextParser parser = new TextParser(fileReader);

              bill = parser.parse();
	      bill.addPhoneCall(call);
	      bill.sortPhoneCalls();
              System.out.println(fileinput.toString() + " Parsed into new bill object.\n\nPrinting newly parsed bill object.");
              bill.printPhone();
            } catch (FileNotFoundException e) {
              throw new RuntimeException(e);
            } catch (ParserException e) {
              throw new RuntimeException(e);
            }
          } else {
            System.out.println("this file doesnt already exist, no parsing can be done");
          }
          try {
            FileWriter fileWriter = new FileWriter(fileinput);
            TextDumper dumper = new TextDumper(fileWriter);

            dumper.dump(bill);

          } catch (FileNotFoundException e) {
            System.err.println("File not found, cannot parse: " + fileinput.toString());
          } //catch (ParserException e) {
          //System.err.println("Error parsing phone bill: " + e.getMessage());
          catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }
        }
        if (args[0].equalsIgnoreCase("-pretty") || args[1].equalsIgnoreCase("-pretty")) {
          File fileinput = null;
          if (args[0].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[1]);
          }
          if (args[1].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[2]);
          }

          try {
            FileWriter fileWriter = new FileWriter(fileinput);
            PrettyPrinter pretty = new PrettyPrinter(fileWriter);
            if (args[1].equalsIgnoreCase("-") ||args[2].equalsIgnoreCase("-") ) {
              System.out.println("STDOUT Pretty Print\n");
              pretty.prettyprint(bill);
            } else {
              pretty.prettyprint(bill);
            }
          } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }

        }

        return;
      }
      //4 Arguments
      if (args.length == 13) {
        if (args[0].equalsIgnoreCase("-readme") || args[1].equalsIgnoreCase("-readme") || args[2].equalsIgnoreCase("-readme") || args[3].equalsIgnoreCase("-readme")) {
          printReadme();
        }
        if (args[0].equalsIgnoreCase("-print") || args[1].equalsIgnoreCase("-print") || args[2].equalsIgnoreCase("-print") || args[3].equalsIgnoreCase("-print")) {
          System.out.println("\nNewest Call\n");
          bill.printPhone();
        }
        if (args[0].equalsIgnoreCase("-textfile") || args[1].equalsIgnoreCase("-textfile") || args[2].equalsIgnoreCase("-textfile")) {
          File fileinput = null;
          if (args[0].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[1]);
          }
          if (args[1].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[2]);
          }
          if (args[2].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[3]);
          }
          if (fileinput.exists() && !fileinput.isDirectory()) {
            try {
              FileReader fileReader = new FileReader(fileinput);

              TextParser parser = new TextParser(fileReader);

              bill = parser.parse();
	      bill.addPhoneCall(call);
	      bill.sortPhoneCalls();
              System.out.println(fileinput.toString() + " Parsed into new bill object.\n\nPrinting newly parsed bill object.");
              bill.printPhone();
            } catch (FileNotFoundException e) {
              throw new RuntimeException(e);
            } catch (ParserException e) {
              throw new RuntimeException(e);
            }
          } else {
            System.out.println("this file doesnt already exist, no parsing can be done");
          }
          try {
            FileWriter fileWriter = new FileWriter(fileinput);
            TextDumper dumper = new TextDumper(fileWriter);

            dumper.dump(bill);

          } catch (FileNotFoundException e) {
            System.err.println("File not found, cannot parse3: " + fileinput.toString());
          } //catch (ParserException e) {
          //System.err.println("Error parsing phone bill: " + e.getMessage());
          catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }

        }
        if (args[0].equalsIgnoreCase("-pretty") || args[1].equalsIgnoreCase("-pretty") || args[2].equalsIgnoreCase("-pretty")) {
          File fileinput = null;
          if (args[0].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[1]);
          }
          if (args[1].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[2]);
          }
          if (args[2].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[3]);
          }
          try {
            FileWriter fileWriter = new FileWriter(fileinput);
            PrettyPrinter pretty = new PrettyPrinter(fileWriter);
            if (args[1].equalsIgnoreCase("-")||args[2].equalsIgnoreCase("-")||args[3].equalsIgnoreCase("-")) {
              System.out.println("STDOUT Pretty Print\n");
              pretty.prettyprint(bill);
            } else {
              pretty.prettyprint(bill);
            }
          } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }

        }

        return;
      }//4 arg bracket
      //5 arguments
      if (args.length == 14) {
        if (args[0].equalsIgnoreCase("-readme") || args[1].equalsIgnoreCase("-readme") || args[2].equalsIgnoreCase("-readme") || args[3].equalsIgnoreCase("-readme") || args[4].equalsIgnoreCase("-readme")) {
          printReadme();
        }
        if (args[0].equalsIgnoreCase("-print") || args[1].equalsIgnoreCase("-print") || args[2].equalsIgnoreCase("-print") || args[3].equalsIgnoreCase("-print") || args[4].equalsIgnoreCase("-print")) {
          System.out.println("\nNewest Call\n");
          bill.printPhone();
        }
        if (args[0].equalsIgnoreCase("-textfile") || args[1].equalsIgnoreCase("-textfile") || args[2].equalsIgnoreCase("-textfile") || args[3].equalsIgnoreCase("-textfile")) {
          File fileinput = null;
          if (args[0].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[1]);
          }
          if (args[1].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[2]);
          }
          if (args[2].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[3]);
          }
          if (args[3].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[4]);
          }
          if (fileinput.exists() && !fileinput.isDirectory()) {
            try {
              FileReader fileReader = new FileReader(fileinput);

              TextParser parser = new TextParser(fileReader);

              bill = parser.parse();
	      bill.addPhoneCall(call);
	      bill.sortPhoneCalls();
              System.out.println(fileinput.toString() + " Parsed into new bill object.\n\nPrinting newly parsed bill object.");
              bill.printPhone();
            } catch (FileNotFoundException e) {
              throw new RuntimeException(e);
            } catch (ParserException e) {
              throw new RuntimeException(e);
            }
          } else {
            System.out.println("this file doesnt already exist, no parsing can be done");
          }
          try {
            FileWriter fileWriter = new FileWriter(fileinput);
            TextDumper dumper = new TextDumper(fileWriter);

            dumper.dump(bill);

          } catch (FileNotFoundException e) {
            System.err.println("File not found, cannot parse3: " + fileinput.toString());
          } //catch (ParserException e) {
          //System.err.println("Error parsing phone bill: " + e.getMessage());
          catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }

        }
        if (args[0].equalsIgnoreCase("-pretty") || args[1].equalsIgnoreCase("-pretty") || args[2].equalsIgnoreCase("-pretty") || args[3].equalsIgnoreCase("-pretty")) {
          File fileinput = null;
          if (args[0].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[1]);
          }
          if (args[1].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[2]);
          }
          if (args[2].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[3]);
          }
          if (args[3].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[4]);
          }
          try {
            FileWriter fileWriter = new FileWriter(fileinput);
            PrettyPrinter pretty = new PrettyPrinter(fileWriter);
            if (args[1].equalsIgnoreCase("-") || args[2].equalsIgnoreCase("-") || args[3].equalsIgnoreCase("-") || args[4].equalsIgnoreCase("-")) {
              System.out.println("STDOUT Pretty Print\n");
              pretty.prettyprint(bill);
            } else {
              pretty.prettyprint(bill);
            }
          } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }
        }
      }
      //5 arg bracket
//6 flags
      if (args.length == 15) {
        if (args[0].equalsIgnoreCase("-readme") || args[1].equalsIgnoreCase("-readme") || args[2].equalsIgnoreCase("-readme") || args[3].equalsIgnoreCase("-readme") || args[4].equalsIgnoreCase("-readme") || args[5].equalsIgnoreCase("-readme")) {
          printReadme();
        }
        if (args[0].equalsIgnoreCase("-print") || args[1].equalsIgnoreCase("-print") || args[2].equalsIgnoreCase("-print") || args[3].equalsIgnoreCase("-print") || args[4].equalsIgnoreCase("-print") || args[5].equalsIgnoreCase("-print")) {
          System.out.println("\nNewest Call\n");
          bill.printPhone();
        }
        if (args[0].equalsIgnoreCase("-textfile") || args[1].equalsIgnoreCase("-textfile") || args[2].equalsIgnoreCase("-textfile") || args[3].equalsIgnoreCase("-textfile") || args[4].equalsIgnoreCase("-textfile")) {
          File fileinput = null;
          if (args[0].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[1]);
          }
          if (args[1].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[2]);
          }
          if (args[2].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[3]);
          }
          if (args[3].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[4]);
          }
          if (args[4].equalsIgnoreCase("-textfile")) {
            fileinput = new File(args[5]);
          }
          if (fileinput.exists() && !fileinput.isDirectory()) {
            try {
              FileReader fileReader = new FileReader(fileinput);

              TextParser parser = new TextParser(fileReader);

              bill = parser.parse();
	      bill.addPhoneCall(call);
	      bill.sortPhoneCalls();
	      
              System.out.println(fileinput.toString() + " Parsed into new bill object.\n\nPrinting newly parsed bill object.");
              bill.printPhone();
            } catch (FileNotFoundException e) {
              throw new RuntimeException(e);
            } catch (ParserException e) {
              throw new RuntimeException(e);
            }
          } else {
            System.out.println("this file doesnt already exist, no parsing can be done");
          }
          try {
            FileWriter fileWriter = new FileWriter(fileinput);
            TextDumper dumper = new TextDumper(fileWriter);

            dumper.dump(bill);

          } catch (FileNotFoundException e) {
            System.err.println("File not found, cannot parse3: " + fileinput.toString());
          } //catch (ParserException e) {
          //System.err.println("Error parsing phone bill: " + e.getMessage());
          catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }

        }
        if (args[0].equalsIgnoreCase("-pretty") || args[1].equalsIgnoreCase("-pretty") || args[2].equalsIgnoreCase("-pretty") || args[3].equalsIgnoreCase("-pretty")) {
          File fileinput = null;
          if (args[0].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[1]);
          }
          if (args[1].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[2]);
          }
          if (args[2].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[3]);
          }
          if (args[3].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[4]);
          }
          if (args[4].equalsIgnoreCase("-pretty")) {
            fileinput = new File(args[5]);
          }
          try {
            FileWriter fileWriter = new FileWriter(fileinput);
            PrettyPrinter pretty = new PrettyPrinter(fileWriter);
            if (args[1].equalsIgnoreCase("-") || args[2].equalsIgnoreCase("-") || args[3].equalsIgnoreCase("-") || args[4].equalsIgnoreCase("-") || args[5].equalsIgnoreCase("-")) {
              System.out.println("STDOUT Pretty Print\n");
              pretty.prettyprint(bill);
            } else {
              pretty.prettyprint(bill);
            }
          } catch (IOException e) {
            System.err.println("I/O error: " + e.getMessage());
          }
        }
      }//6 arg bracket
      return;
    }//isvalid bracket

  }//main bracket
  public static LocalDateTime parsetime(String date, String time, String ampm){
    String dateinfo = date + " " + time + " " + ampm;

    DateTimeFormatter formatter = null;
    //1/1/1111
    if(date.matches("[1-9]/[1-9]/\\d{4}")){

      //11:11
      if(time.matches("(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("M/d/yyyy hh:mm a");

      }
      if(time.matches("[1-9]:([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("M/d/yyyy h:mm a");
      }
    }
    //1/11/1111
    if(date.matches("[1-9]/(0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}")){
      if(time.matches("(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("M/dd/yyyy hh:mm a");

      }
      if(time.matches("[1-9]:([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("M/dd/yyyy h:mm a");

      }
    }
    //11/11/1111
    if(date.matches("(0[1-9]|1[0-2])/(0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}")){
      if(time.matches("(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("MM/dd/yyyy hh:mm a");

      }
      if(time.matches("[1-9]:([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("MM/dd/yyyy h:mm a");

      }
    }
    //1/1/11
    if(date.matches("[1-9]/[1-9]/\\d{2}")){

      //11:11
      if(time.matches("(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("M/d/yy hh:mm a");

      }
      if(time.matches("[1-9]:([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("M/d/yy h:mm a");
      }
    }
    //1/11/1111
    if(date.matches("[1-9]/(0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{2}")){
      if(time.matches("(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("M/dd/yy hh:mm a");

      }
      if(time.matches("[1-9]:([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("M/dd/yy h:mm a");

      }
    }
    //11/11/1111
    if(date.matches("(0[1-9]|1[0-2])/(0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{2}")){
      if(time.matches("(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("MM/dd/yy hh:mm a");

      }
      if(time.matches("[1-9]:([0-5][0-9])")){
        formatter = DateTimeFormatter.ofPattern("MM/dd/yy h:mm a");

      }
    }
    if(formatter == null){
      System.err.println("cant find pattern");
      return null;
    }
    LocalDateTime timeinfo = LocalDateTime.parse(dateinfo, formatter);

    return timeinfo;
  }
  //Check Caller & Callee Format
  public static boolean checkFormat(String [] args){
    boolean pass= true;
    //Check Caller
    if (!args[args.length -8].matches("[0-9-]+")) {
      System.err.println("There was an error in the caller format, there are special characters, please use the option -README for more information\"");
      pass = false;
    }else if(args[args.length -8].length() != 12){
      System.err.println("There was an error in the caller format, there are too many numbers used, please use the option -README for more information");
      pass = false;
    }

    //Check Callee
    if (!args[args.length -7].matches("[0-9-]+")) {
      System.err.println("There was an error in the callee format, there are special characters, please use the option -README for more information\"");
      pass = false;
    }if(args[args.length -7].length() > 12){
      System.err.println("There was an error in the callee format, there are too many numbers used, please use the option -README for more information");
      pass = false;
    }else if(args[args.length -7].length() < 12){
      System.err.println("There was an error in the callee format, there are not enough numbers used, please use the option -README for more information");
      pass = false;
    }



    //Check dates and times
    boolean pass2 =checkDateFormat(args);
    if(pass2 == false || pass == false) {
      return false;
    }else{
      return true;
    }

  }
  //Check Date and Time
  public static boolean checkDateFormat(String [] args){

    boolean pass = true;
    //Check Begin Date

    //Check Range
    if((args[args.length -6].length() < 8 || args[args.length -6].length() > 10)) {
      System.err.println("There was an error in the begin date format, theres not enough numbers, please use the -README option for more help");
      pass = false;
    }

    //Format of 1/1/1111
    else if(args[args.length -6].length() == 8){
      if(!args[args.length -6].matches("[1-9]/[1-9]/\\d{4}")){
        System.err.println("There was an error in the begin date format, this date does not exist, please use the -README option for more help");
        pass = false;
      }
    }

    //Format of 1/11/1111 or 11/1/1111
    else if(args[args.length -6].length() == 9) {
      if (!args[args.length -6].matches("[1-9]/([1-9]|0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}") && !args[args.length -6].matches("([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9])/\\d{4}")) {
        System.err.println("There was an error in the begin date format, this day does not exist, please use the -README option for more help");
        pass = false;
      }
    }

    //Format of 11/11/1111
    else{
      if(!args[args.length -6].matches("([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}")) {

        System.err.println("There was an error in the begin date format,  this day does not exist, please use the -README option for more help");
        pass = false;
      }
    }

    //Check Begin Time

    //Check Range
    if(args[args.length -5].length() < 4 || args[args.length -5].length() > 5){
      System.err.println("There was an error in the begin time format, the number placement is off, please use the -README option for more help");
      pass = false;
    }
    //Format of 1:11
    if(args[args.length -5].length() ==4){
      if(!args[args.length -5].matches("[1-9]:([0-5][0-9])")){
        System.err.println("There was an error in the begin time format, this time isn't supported on the 24 hour clock, please use the -README option for more help");
        pass = false;

      }
    }
    //Format of 11:11
    if(args[args.length -5].length() ==5) {
      if (!args[args.length -5].matches("(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])")){
        System.err.println("There was an error in the begin time format, this time isn't supported on the 24 hour clock, please use the -README option for more help");
        pass = false;
      }
    }

    //Check End Date

    //Check Range
    if((args[args.length -3].length() < 8 || args[args.length -3].length() > 10)) {
      System.err.println("There was an error in the end date format, theres not enough numbers, please use the -README option for more help");
      pass = false;;
    }
    //Format of 1/1/1111
    else if(args[args.length -3].length() == 8){
      if(!args[args.length -3].matches("[1-9]/[1-9]/\\d{4}")){
        System.err.println("There was an error in the end date format, this date does not exist, please use the -README option for more help");
        pass = false;
      }
    }
    //Format of 1/11/1111 or //Format of 11/1/1111
    else if(args[args.length -3].length() == 9) {
      if (!args[args.length -3].matches("[1-9]/([1-9]|0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}") && !args[args.length -3].matches("([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9])/\\d{4}")) {
        System.err.println("There was an error in the end date format, this date does not exist, please use the -README option for more help");
        pass = false;
      }
    }
    //Format of 11/11/1111
    else{
      if(!args[args.length -3].matches("([1-9]|0[1-9]|1[0-2])/([1-9]|0[1-9]|1[0-9]|2[0-9]|3[0-1])/\\d{4}")) {

        System.err.println("There was an error in the end date format, this date does not exist, please use the -README option for more help");
        pass = false;
      }
    }

    //Check End Time

    //Check Range
    if(args[args.length -2].length() < 4 || args[args.length -2].length() > 5){
      System.err.println("There was an error in the End time format, the number placement is off, please use the -README option for more help");
      pass = false;
    }
    //Format of 1:11
    if(args[args.length -2].length() ==4){
      if(!args[args.length -2].matches("[1-9]:([0-5][0-9])")){
        System.err.println( "There was an error in the End time format, this time isn't supported on the 24 hour clock, please use the -README option for more help");
        pass = false;

      }
    }
    //Format of 11:11
    if(args[args.length -2].length() ==5) {
      if (!args[args.length -2].matches("(1[0-9]|2[0-3]):([0-5][0-9])")){
        System.err.println("There was an error in the End time format, this time isn't supported on the 24 hour clock, please use the -README option for more help");
        pass = false;
      }
    }

    return pass;
  }

  //Check Amount of arguments
  public static boolean checkArguments(String [] args) {

    if (args.length == 0 || args == null) {
      System.err.println("\nPlease run the program with command line arguments\nExample: java -jar target/phonebill-1.0.0.jar <options> <arguments>\n\nRun the script with -README option for more help. [ java -jar target/phonebill-1.0.0.jar -README ]");
      return false;
    }
    for (String arg : args) {
      if (arg == null) {
        System.err.println("\nOne of the arguments is null. Please provide valid arguments.\n");
        return false;
      }
    }

    // Check for null or empty arguments
    if (args.length < 9) {
      System.err.println("\nThere are missing arguments");
      System.err.println("\nPlease run the program with command line arguments\nExample: ./runscript *options* 'Name' '000-000-000' '000-000-000' '12/12/2000' '12:12' '12/22/12' '12:12'\n");

      return false;
    }

    if (args.length == 9) {
      for (String arg : args) {
        if (arg.equalsIgnoreCase("-textfile") || args[0].equalsIgnoreCase("-print") || args[0].equalsIgnoreCase("-readme")) {
          System.err.println("\nPlease run the program with command line arguments\nExample: ./runscript *options* 'Name' '000-000-000' '000-000-000' '12/12/2000' '12:12' '12/22/12' '12:12'\n");
          return false;
        }
      }
    }

    if (args.length > 15) {
      System.err.println("\nThere are extraneous arguments");
      System.err.println("\nPlease run the program with command line arguments\nExample: ./runscript *options* 'Name' '000-000-000' '000-000-000' '12/12/2000' '12:12' '12/22/12' '12:12'\n");
      return false;
    }


    //one flag

    if (args.length == 10) {
      if (args[0].equalsIgnoreCase("-textfile") || args[0].equalsIgnoreCase("-pretty") ) {
        System.err.println(args[0] + " must have a file after it");
        return false;
      }
      if (args[0].equalsIgnoreCase("-print") || args[0].equalsIgnoreCase("-readme")) {
        return checkFormat(args);
      } else if (!args[1].matches("[0-9-]+") || args[1].length() != 12) {
        System.err.println(args[0] + " must be a valid argument, there are extraneous arguments");
        return false;
      } else {
        System.err.println(args[7] + " must be a valid argument, there are extraneous arguments");
        return false;
      }

    }
    //two flags

    if (args.length == 11) {
      if (args[1].equalsIgnoreCase("-textfile") || args[1].equalsIgnoreCase("-pretty")) {
        System.err.println(args[1] + " must have a file after it");
        return false;
      }
      if (!args[0].equalsIgnoreCase("-print") && !args[0].equalsIgnoreCase("-readme") && !args[0].equalsIgnoreCase("-textfile") && !args[0].equalsIgnoreCase("-pretty")) {
        System.err.println(args[0] + " must be -print, -textfile, -pretty  or -readme");
        return false;
      }
      if (!args[1].equalsIgnoreCase("-print") && !args[1].equalsIgnoreCase("-readme") && !args[1].equalsIgnoreCase("-textfile")) {
        if (args[0].equalsIgnoreCase("-textfile") || args[0].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        System.err.println(args[1] + " must be -print, -textfile, -pretty  or -readme");
        return false;
      }
      if (args[0].equalsIgnoreCase("-print") || args[0].equalsIgnoreCase("-readme")) {
        return checkFormat(args);
      } else {
        System.err.println(args[0] + " must be -print, -textfile, -pretty  or -readme");
        return false;
      }
    }

    //three flags
    if (args.length == 12) {

      //first flag
      if (!args[0].equalsIgnoreCase("-print") && !args[0].equalsIgnoreCase("-readme") && !args[0].equalsIgnoreCase("-textfile") && !args[0].equalsIgnoreCase("-pretty")) {
        //options at end
        if (!args[1].matches("[0-9-]+") || args[1].length() != 12) {
          System.err.println(args[0] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //second flag
      if (!args[1].equalsIgnoreCase("-print") && !args[1].equalsIgnoreCase("-readme") && !args[1].equalsIgnoreCase("-textfile")) {
        if (args[0].equalsIgnoreCase("-textfile") || args[0].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[2].matches("[0-9-]+") || args[2].length() != 12) {
          System.err.println(args[1] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //third flag
      if (!args[2].equalsIgnoreCase("-print") && !args[2].equalsIgnoreCase("-readme") && !args[2].equalsIgnoreCase("-textfile") && !args[2].equalsIgnoreCase("-pretty")) {
        if (args[1].equalsIgnoreCase("-textfile") || args[1].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[3].matches("[0-9-]+") || args[3].length() != 12) {
          System.err.println(args[2] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      if (args[2].equalsIgnoreCase("-print") || args[2].equalsIgnoreCase("-readme")) {
        return checkFormat(args);
      }
      if (args[2].equalsIgnoreCase("-textfile") || args[2].equalsIgnoreCase("-pretty") ) {
        if(!args[3].matches("[0-9-]+") && !args[4].matches("[0-9-]+")){
          System.err.println("Error: missing phone call argument");
          return false;
        }
        System.err.println(args[2] + " must have a file after it");
        return false;
      } else {
        System.err.println(args[2] + " must be -print, -textfile, -pretty, or -readme");
        return false;
      }
    }
    //4 flags
    if (args.length == 13) {
      //first flag
      if (!args[0].equalsIgnoreCase("-print") && !args[0].equalsIgnoreCase("-readme") && !args[0].equalsIgnoreCase("-textfile") && !args[0].equalsIgnoreCase("-pretty")) {
        //options at end
        if (!args[1].matches("[0-9-]+") || args[1].length() != 12) {
          System.err.println(args[0] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //second flag
      if (!args[1].equalsIgnoreCase("-print") && !args[1].equalsIgnoreCase("-readme") && !args[1].equalsIgnoreCase("-textfile") && !args[1].equalsIgnoreCase("-pretty")) {
        if (args[0].equalsIgnoreCase("-textfile") || args[0].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[2].matches("[0-9-]+") || args[2].length() != 12) {
          System.err.println(args[1] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //third flag
      if (!args[2].equalsIgnoreCase("-print") && !args[2].equalsIgnoreCase("-readme") && !args[2].equalsIgnoreCase("-textfile") && !args[2].equalsIgnoreCase("-pretty")) {
        if (args[1].equalsIgnoreCase("-textfile") || args[1].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[3].matches("[0-9-]+") || args[3].length() != 12) {
          System.err.println(args[2] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //fourth flag
      if (!args[3].equalsIgnoreCase("-print") && !args[3].equalsIgnoreCase("-readme") && !args[3].equalsIgnoreCase("-textfile") && !args[3].equalsIgnoreCase("-pretty")) {
        if (args[2].equalsIgnoreCase("-textfile") || args[2].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[4].matches("[0-9-]+") || args[4].length() != 12) {
          System.err.println(args[3] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      if (args[3].equalsIgnoreCase("-print") || args[3].equalsIgnoreCase("-readme")) {
        return checkFormat(args);
      }
      if (args[3].equalsIgnoreCase("-textfile") || args[3].equalsIgnoreCase("-pretty")) {
        if(!args[4].matches("[0-9-]+") && !args[5].matches("[0-9-]+")){
          System.err.println("Error: missing phone call argument");
          return false;
        }
        System.err.println(args[3] + " must have a file after it");
        return false;
      } else {
        System.err.println(args[3] + " must be -print, -textfile, -pretty, or -readme");
        return false;
      }
    }
//5 flags
    if (args.length == 14) {
      //first flag
      if (!args[0].equalsIgnoreCase("-print") && !args[0].equalsIgnoreCase("-readme") && !args[0].equalsIgnoreCase("-textfile") && !args[0].equalsIgnoreCase("-pretty")) {
        //options at end
        if (!args[1].matches("[0-9-]+") || args[1].length() != 12) {
          System.err.println(args[0] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //second flag
      if (!args[1].equalsIgnoreCase("-print") && !args[1].equalsIgnoreCase("-readme") && !args[1].equalsIgnoreCase("-textfile") && !args[1].equalsIgnoreCase("-pretty")) {
        if (args[0].equalsIgnoreCase("-textfile") || args[0].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[2].matches("[0-9-]+") || args[2].length() != 12) {
          System.err.println(args[1] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //third flag
      if (!args[2].equalsIgnoreCase("-print") && !args[2].equalsIgnoreCase("-readme") && !args[2].equalsIgnoreCase("-textfile") && !args[2].equalsIgnoreCase("-pretty")) {
        if (args[1].equalsIgnoreCase("-textfile") || args[1].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[3].matches("[0-9-]+") || args[3].length() != 12) {
          System.err.println(args[2] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //fourth flag
      if (!args[3].equalsIgnoreCase("-print") && !args[3].equalsIgnoreCase("-readme") && !args[3].equalsIgnoreCase("-textfile") && !args[3].equalsIgnoreCase("-pretty")) {
        if (args[2].equalsIgnoreCase("-textfile") || args[2].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[4].matches("[0-9-]+") || args[4].length() != 12) {
          System.err.println(args[3] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //Fifth flag
      if (!args[4].equalsIgnoreCase("-print") && !args[4].equalsIgnoreCase("-readme") && !args[4].equalsIgnoreCase("-textfile") && !args[4].equalsIgnoreCase("-pretty")) {
        if (args[3].equalsIgnoreCase("-textfile") || args[3].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[5].matches("[0-9-]+") || args[5].length() != 12) {
          System.err.println(args[3] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      if (args[4].equalsIgnoreCase("-print") || args[4].equalsIgnoreCase("-readme")) {
        return checkFormat(args);
      }
      if (args[4].equalsIgnoreCase("-textfile") || args[4].equalsIgnoreCase("-pretty")) {
        if(!args[5].matches("[0-9-]+") && !args[6].matches("[0-9-]+")){
          System.err.println("Error: missing phone call argument");
          return false;
        }
        System.err.println(args[4] + " must have a file after it");
        return false;
      } else {
        System.err.println(args[4] + " must be -print, -textfile, -pretty, or -readme");
        return false;
      }
    }
    //6 flags
    if (args.length == 15) {
      //first flag
      if (!args[0].equalsIgnoreCase("-print") && !args[0].equalsIgnoreCase("-readme") && !args[0].equalsIgnoreCase("-textfile") && !args[0].equalsIgnoreCase("-pretty")) {
        //options at end
        if (!args[1].matches("[0-9-]+") || args[1].length() != 12) {
          System.err.println(args[0] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //second flag
      if (!args[1].equalsIgnoreCase("-print") && !args[1].equalsIgnoreCase("-readme") && !args[1].equalsIgnoreCase("-textfile") && !args[1].equalsIgnoreCase("-pretty")) {
        if (args[0].equalsIgnoreCase("-textfile") || args[0].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[2].matches("[0-9-]+") || args[2].length() != 12) {
          System.err.println(args[1] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //third flag
      if (!args[2].equalsIgnoreCase("-print") && !args[2].equalsIgnoreCase("-readme") && !args[2].equalsIgnoreCase("-textfile") && !args[2].equalsIgnoreCase("-pretty")) {
        if (args[1].equalsIgnoreCase("-textfile") || args[1].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[3].matches("[0-9-]+") || args[3].length() != 12) {
          System.err.println(args[2] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //fourth flag
      if (!args[3].equalsIgnoreCase("-print") && !args[3].equalsIgnoreCase("-readme") && !args[3].equalsIgnoreCase("-textfile") && !args[3].equalsIgnoreCase("-pretty")) {
        if (args[2].equalsIgnoreCase("-textfile") || args[2].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[4].matches("[0-9-]+") || args[4].length() != 12) {
          System.err.println(args[3] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //Fifth flag
      if (!args[4].equalsIgnoreCase("-print") && !args[4].equalsIgnoreCase("-readme") && !args[4].equalsIgnoreCase("-textfile") && !args[4].equalsIgnoreCase("-pretty")) {
        if (args[3].equalsIgnoreCase("-textfile") || args[3].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[5].matches("[0-9-]+") || args[5].length() != 12) {
          System.err.println(args[3] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      //Sixth flag
      if (!args[5].equalsIgnoreCase("-print") && !args[5].equalsIgnoreCase("-readme") && !args[5].equalsIgnoreCase("-textfile") && !args[5].equalsIgnoreCase("-pretty")) {
        if (args[4].equalsIgnoreCase("-textfile") || args[4].equalsIgnoreCase("-pretty")) {
          return checkFormat(args);
        }
        if (!args[6].matches("[0-9-]+") || args[6].length() != 12) {
          System.err.println(args[4] + " must be a valid option, do -README for more help");
          return false;
        }
        System.err.println("there are extraneous arguments, all options need to be put in front. please do -README for more help");
        return false;
      }
      if (args[5].equalsIgnoreCase("-print") || args[5].equalsIgnoreCase("-readme")) {
        return checkFormat(args);
      }
      if (args[5].equalsIgnoreCase("-textfile") || args[5].equalsIgnoreCase("-pretty")) {
        if(!args[6].matches("[0-9-]+") && !args[7].matches("[0-9-]+")){
          System.err.println("Error: missing phone call argument");
          return false;
        }
        System.err.println(args[5] + " must have a file after it");
        return false;
      } else {
        System.err.println(args[5] + " must be -print, -textfile, -pretty, or -readme");
        return false;
      }
    }
    return checkFormat(args);
  }
  public static void printReadme(){
    String readmeFileName = "/u/dahuynh/git/joyofcoding/TheJoyOfCodingSummer2024/phonebill/src/main/resources/edu/pdx/cs/joy/dahuynh/README.txt";

    try (BufferedReader reader = new BufferedReader(new FileReader(readmeFileName))) {
      String line;
      while ((line = reader.readLine()) != null) {
        System.out.println(line);
      }
    } catch (IOException e) {
      System.err.println("Error reading the readme file: " + e.getMessage());
    }
  }
}
