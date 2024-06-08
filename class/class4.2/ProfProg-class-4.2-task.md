**TASK. Adapter for calculator**

As a part of this task you will get the following files:
- ModernCalculators.hpp - header file with the latest-greatest interface for calculators. Also it contains two child classes - ConstantCalculator and MyCoolCalculator.
- LegacyCalculator.hpp - some old algorithm for calculations.
- main.cpp - file with general logic to call some calculations and also a function to print the result summary of calculations.

1. Review the usage of unique pointers in main.cpp. Take a look at unique_ptr and inheritance.
2. Review the ModernCalculators.hpp header to understand the general interface of the classes.
3. Review LegacyCalculator.hpp - it has completelyy different interface.

Main task: You should create one more header MegaAdapter.hpp and uncomment both include and commented logic in main.cpp. MegaAdapter.hpp should contain a MegaAdapter class that supports BaseMegaCalculator interface and adapts interface of LegacyCalculator. Important note in legacy calculator price was splitted into 2 checks while for the new interface it can be adapted as sum of that components.
You are NOT ALLOWED to mofify LegacyCalculator class it self.
After all the changes program should be run properly with uncommented parts of main.cpp

