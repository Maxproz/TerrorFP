// Copyright @Maxpro 2016

#pragma once

/**
 * 
 */
class TERRORFP_API StaticConstantNames
{
public:
	StaticConstantNames();
	~StaticConstantNames();
    
    static const int32 EmptyID = 0;
    static const int32 WoodID = 1;
    static const int32 KeyID = 2;
    static const int32 TinderBoxID = 3;
    
    /* // using static member function template below.
     
     private:
     static int s_nextID; // Here's the declaration for a static member
     
     public:
     static int getNextID(); // Here's the declaration for a static function
     };
     
     // Here's the definition of the static member outside the class.  Note we don't use the static keyword here.
     // We'll start generating IDs at 1
     int IDGenerator::s_nextID = 1;
     
     // Here's the definition of the static function outside of the class.  Note we don't use the static keyword here.
     int IDGenerator::getNextID() { return s_nextID++; }
     
     */
    
};
