/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12
 Create a branch named Part1
Purpose:  This project continues developing Project3.
       you will learn how to take code from existing projects and migrate only what you need to new projects
       you will learn how to write code that doesn't leak as well as how to refactor. 
Since you didn't do Project 3:
write 3 UDTs below (where it asks for Copied UDTs) that EACH have: 
        5 member variables
            the member variable names and types should be relevant to the work the UDT will perform.
        3 member functions with an arbitrary number of parameters
            give some of those parameters default values.
        constructors that initialize some of these member variables
            the remaining member variables should be initialized in-class
        for() or while() loops that modify member variables
 1) 2 of your 3 UDTs need to have a nested UDT.
    this nested UDT should fulfill the same requirements as above:
        5 member variables  
        3 member functions
        constructors and loops.
        
 2) Define your implementations of all functions OUTSIDE of the class. 
 NO IN-CLASS IMPLEMENTATION ALLOWED
 3) add destructors to all of your UDTs
        make the destructors do something like print out the name of the class.
 
 4) add 2 new UDTs that use only the types you copied above as member variables.
 
 5) Add destructors to these 2 new types that do something.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 6) use at least 2 instances of each of your UDTs in main. 
        add some std::cout statements in main() that use your UDT's member variables.
 
 7) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
If you need inspiration for what to write, take a look at previously approved student projects in the Slack Workspace channel for this project part.
 */

/*
 UDT 1:
 */
#include <iostream>

struct Animal
{
    int totalCalories;
    bool isHungry = true;
    int mealsEaten;
    float distanceWalked;    
    float animalHeight{ 8.2f };

    Animal();
    ~Animal();
    void walk( float currentPace, int timeWalked, bool walkForward);
    void grow( float growthHeight = 0.2f );
    void consume( int calorieAmount = 1600 );

};

Animal::Animal() : 
totalCalories( 2600 ),
mealsEaten(3),
distanceWalked( 150.5f ) {}

Animal::~Animal()
{
    std::cout << "Animal Destroyed" << std::endl;
}

void Animal::walk(float currentPace, int timeWalked, bool walkForward)
{
   if( walkForward )
   {
       distanceWalked += (currentPace * timeWalked); 
   } 
   else
   {
       distanceWalked -= (currentPace * timeWalked);
   }
}

void Animal::grow(float growthHeight)
{
    for(int i = 0; i < 6; ++i )
    {
        animalHeight += growthHeight;
    }
}

void Animal::consume( int calorieIntake )
{
    if(isHungry)
    {
        totalCalories += calorieIntake;
        mealsEaten++;
        isHungry = false;
    }
}

/*
 UDT 2:
 */
struct Ball
{
    double ballRadius;
    float ballWeight;
    bool canRoll = true;
    bool isBouncy = false;
    int numberOfDimples = 201;

    struct Sandball
    {
        float percentFilled = 75.0f;
        bool plasticCoating = false;
        float sandWeight;
        bool fineSandFilling;
        int lengthOfTail;

        Sandball();
        ~Sandball();
        void fillBall(int howLong);
        void changeFilling();
        void cutTail(int cutAmount);
    };

    Ball();
    ~Ball();
    void getHeavier(bool soakInWater, int soakingTime = 3);
    double getVolume(bool isHollow);
    void addDimples(int howManyToAdd);
};

Ball::Ball() : 
ballRadius(2.5),
ballWeight(4.2f){}

Ball::~Ball()
{
    std::cout << "Ball Destroyed" << std::endl;
}

void Ball::getHeavier(bool soakInWater, int soakingTime)
{
    if(soakInWater)
    {
        while(soakingTime > 0)
        {
            //std::cout << "Soaked Ball" << std::endl;
            --soakingTime;
            ballWeight += 0.2f;
        }
    }
}

double Ball::getVolume(bool isHollow)
{
    if(isHollow)
    {
        return 0.0;
    }
    return (4/3)*(3.14159)*(ballRadius * ballRadius);
}

void Ball::addDimples(int howManyToAdd)
{
    numberOfDimples += howManyToAdd;
}

Ball::Sandball::Sandball() :
    sandWeight(5.1f),
    fineSandFilling(true),
    lengthOfTail(15)
    {}

Ball::Sandball::~Sandball()
{
    std::cout << "Sandball Destroyed" << std::endl;
}

void Ball::Sandball::fillBall(int howLong)
{
    while(howLong > 0)
    {
        percentFilled++;
        sandWeight = sandWeight + 0.1f;        
        --howLong;
    }
}

void Ball::Sandball::changeFilling()
{
    fineSandFilling = !fineSandFilling;
}

void Ball::Sandball::cutTail(int cutAmount)
{
    lengthOfTail -= cutAmount;
}

/*
 UDT 3:
 */

struct Bird
{
    float birdWeight;
    double groundSpeed{3.4};
    double distanceWaddled{104.4};
    bool webbedFeet = false;
    bool sharpBill;

    Bird();
    ~Bird();
    bool canSwim(bool birdFloats);
    void eatMeal(float mealWeight, bool mealInShell);
    void waddle(int timeWaddling);

    struct FlyingBird
    {
        float flightSpeed;
        int flapsPerMinute;
        double migrationDistance;
        bool flysInFlocks = true;
        float lengthOfWings{4.5f};

        FlyingBird();
        ~FlyingBird();
        void migrate(bool flySouth, double tripDistance);
        int flapsPerTrip(int minutesPerTrip);
        void growWings(float growthAmount);

    };
};

Bird::Bird() : 
birdWeight(10.f),
sharpBill(false)
{}

Bird::~Bird()
{
    std::cout << "Bird Destroyed" << std::endl;
}

bool Bird::canSwim(bool birdFloats)
{
    return birdFloats && webbedFeet;
}

void Bird::eatMeal(float mealWeight, bool mealInShell)
{
    if(mealInShell && sharpBill)
    {
        birdWeight += mealWeight;
    }
}

void Bird::waddle(int timeWaddling)
{
    while(timeWaddling > 0)
    {
        distanceWaddled += groundSpeed;
        --timeWaddling;
    }
}

Bird::FlyingBird::FlyingBird() :
flightSpeed(25.3f),
flapsPerMinute(45),
migrationDistance(0)
{}

Bird::FlyingBird::~FlyingBird()
{
    std::cout << "FlyingBird Destroyed" << std::endl;
}

void Bird::FlyingBird::migrate(bool flySouth, double tripDistance)
{
    if(flySouth)
    {
        migrationDistance += tripDistance;
    }
}

int Bird::FlyingBird::flapsPerTrip(int minutesPerTrip)
{
    return minutesPerTrip * flapsPerMinute;
}

void Bird::FlyingBird::growWings(float growthAmount)
{
    lengthOfWings += growthAmount;
}
/*
 new UDT 4:
 */

struct Zoo
{
    Animal ferret;
    Bird::FlyingBird parrot;
    Bird penguin;

    Zoo(){}
    ~Zoo();
};

Zoo::~Zoo()
{
    std::cout << "The parrot's wings were " << parrot.lengthOfWings << " inches long" << std::endl;
    parrot.growWings(0.5f);
    std::cout << "Now they are " << parrot.lengthOfWings << " inches long" << std::endl;
}

/*
 new UDT 5:
 */

struct BagOfBalls
{
    Ball golfBall;
    Ball soccerBall;
    Ball::Sandball hackySack;

    BagOfBalls(){}
    ~BagOfBalls();
};

BagOfBalls::~BagOfBalls()
{
    std::cout << "The bag of balls has been destroyed" << std::endl;
}

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.
 send me a DM to review your pull request when the project is ready for review.
 Wait for my code review.
 */


int main()
{
    Zoo Bronx;
    Zoo Philly;
    BagOfBalls coachBag;
    BagOfBalls practiceBag;
    Animal dog;
    Animal horse;
    Bird::FlyingBird swallow;
    Bird emu;
    Ball baseball;
    Ball::Sandball weightedBall;

    dog.consume(2400);
    std::cout << "The dog has eaten " << dog.totalCalories << " calories" << std::endl;

    horse.walk(2.1f, 60, true);
    std::cout << "The horse walked " << horse.distanceWalked << " miles" << std::endl;

    int tripA = 90;
    int tripB = 60;
    
    std::cout << "On a " << tripA << " minute trip a swallow flaps it's wings " << swallow.flapsPerTrip(tripA) << " times" << std::endl;

    std::cout << "On a " << tripB << " minute trip a swallow flaps it's wings " << swallow.flapsPerTrip(tripB) << " times" << std::endl;

    emu.webbedFeet = true;
    std::string result;
    (emu.canSwim(true)) ? result = "can swim." : result = "can't swim.";
    std::cout << "In the water the emu " << result << std::endl;

    std::cout << "The baseball weighed " << baseball.ballWeight << " ounces" << std::endl;
    baseball.getHeavier(true, 2);
    std::cout << "I left the baseball in the rain and it now weighs " << baseball.ballWeight << " ounces" << std::endl;

    std::cout << "The weighted ball was " << weightedBall.percentFilled << " percent filled" << std::endl;
    weightedBall.fillBall(10);
    std::cout << "I filled it more and it is now " << weightedBall.percentFilled << " percent filled" << std::endl;

    Bronx.parrot.migrate(true, 200);
    std::cout << "They let their parrot migrate for the winter and it flew " << Bronx.parrot.migrationDistance << " miles South" << std::endl;

    Philly.parrot.migrate(true, 600);
    std::cout << "Philly also let their parrot migrate for the winter and it flew " << Philly.parrot.migrationDistance << " miles South" << std::endl;

    std::cout << "The golf ball in the coach bag started out with " << coachBag.golfBall.numberOfDimples << " dimples" << std::endl;
    coachBag.golfBall.addDimples(15);
    std::cout << "The golf ball from the coach bag now has " << coachBag.golfBall.numberOfDimples << " dimples" << std::endl;

    std::cout << "We changed the filling in the hackySack from ";
    practiceBag.hackySack.fineSandFilling ? (std::cout << "fine sand") : (std::cout << "coarse sand");
    practiceBag.hackySack.changeFilling();
    std::cout << " to ";
    practiceBag.hackySack.fineSandFilling ? (std::cout << "fine sand\n") : (std::cout << "coarse sand\n");

    std::cout << "good to go!" << std::endl;
}
