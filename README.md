# James Folk - Trellis Test 

## Problem


In order to request an insurance quote from The Colonel Insurance, they require the following fields:
    - the address of the policy holder
    - the name of the policy holder
    - the email address of the policy holder
    - the complete driver’s license number of the policy holder
    - the exact date of birth of all operators
    - the gender of all operators

Please submit a function that takes in a single policy and returns a list of the required fields that are not available in the policy. The file policies.json contains an array of example policies you can use to aid you in the development of your function.

Your function should return exactly what information our support team needs to ask for in order to have a complete policy that we can use to request quotes from The Colonel Insurance.

**The function I wrote is `PolicyParser::get()->parse(string(t), policies)`. PolicyParser is a singleton and strategy class pattern. It has a `printRuleErrors` function used to communicate to the human operators the policy ids that do not have all the required fields for a given insurance company.
The code is written so that it can be built for any platform and run fast. I was tempted to wrap the code using [SWIG](http://www.swig.org/), but the project is not meant to be that long. If I were to do that, I would wrap it for python, javascript and, Lua first.**
* **Written in C++17 with cmake 3.15.3 to build an IDE for the test.**
* **The data model using an online tool: https://quicktype.io/**
* **The core functionlity is built into a static library.**
* **The problem test is written into the executable, which uses the static library.**

## Other Considerations


Suppose that in addition to generating quotes from The Colonel Insurance, we also wanted to request quotes from Ranchers Insurance. However, the set of fields that Ranchers Insurance requires to generate quotes is slightly different - e.g. don’t require gender, but they want the license numbers for all operators and also want the policy holder’s phone number. How would this affect your solution?
Suppose that instead of being consumed by a support team member, the list of questions was going to be used to power a programmatic, online interview flow. Would there be anything you would change in your solution?

**I implemented sample code that shows how I would architect this.  When running `PolicyParser::printRuleErrors`, you pass in a `RuleType` strategy. The strategy runs an overloaded function to either print out the invalid parameters for people. The developer can create subclasses to the `RuleType` strategies to define specific rules for different insurance companies. In my example, I created the rules for The Colonel Insurance and Ranchers Insurance based on your example requirements. There is also another strategy, which can be used to fill up a POD class of the invalid parameters so that it can be used in another process. I chose not to develop the adapter function in the PolicyParser, but that is all that is need, the core functionality is developed in the `ColonelRules::hasRuleIssues` and `RanchersRules::hasRuleIssues` functions. I tried to architect this to follow the SOLID principles of object oriented development. The library owner can distribute the PolicyParser as a binary library to be consumed by third party developers.**

### How to build
```
mkdir build
cd build
cmake ..
make
```

### How to run
```
cd build
./trellis-exe 
```

