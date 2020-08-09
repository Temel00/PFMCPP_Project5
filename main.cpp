/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 3) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 4) write the name of your class where it says "OwnerClass"
 
 5) write wrapper classes for each type similar to how it was shown in the video
 
 7) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
 Axe axe;
 std::cout << "axe sharpness: " << axe.sharpness << "\n";
 #endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 you can safely ignore any warnings about exit-time-destructors.
 if you would like to suppress them, add -Wno-exit-time-destructors to the .replit file 
   with the other warning suppression flags
 */


/*
 UDT 1:
 */
#include <iostream>
#include "LeakedObjectDetector.h"

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
    void walkCopy()
    {
        std::cout << "The animal walked " << this->distanceWalked << " miles" << std::endl;
    }
    void grow( float growthHeight = 0.2f );
    void consume( int calorieAmount = 1600 );
    void consumeCopy()
    {
        std::cout << "The animal has eaten " << this->totalCalories << " calories" << std::endl;
    }
    JUCE_LEAK_DETECTOR(Animal)
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

struct AnimalWrapper
{
    AnimalWrapper(Animal* ptr) : pointerToAnimal( ptr ){}
    ~AnimalWrapper()
    {
        delete pointerToAnimal;
    }
    Animal* pointerToAnimal = nullptr;
};


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
        void fillBallCopy()
        {
            std::cout << "The weighted ball was " << this->percentFilled << " percent filled" << std::endl;
            this->fillBall(10);
            std::cout << "I filled it more and it is now " << this->percentFilled << " percent filled" << std::endl;
        }
        void changeFilling();
        void changeFillingCopy()
        {
            std::cout << "We changed the filling in the hackySack from ";
        this->fineSandFilling ? (std::cout << "fine sand") : (std::cout << "coarse sand");
        this->changeFilling();
        std::cout << " to ";
        this->fineSandFilling ? (std::cout << "fine sand\n") : (std::cout << "coarse sand\n");
        }
        void cutTail(int cutAmount);
        JUCE_LEAK_DETECTOR(Sandball)
    };

    Ball();
    ~Ball();
    void getHeavier(bool soakInWater, int soakingTime = 3);
    void getHeavierCopy()
    {
        std::cout << "The baseball weighed " << this->ballWeight << " ounces" << std::endl;
        this->getHeavier(true, 2);
        std::cout << "I left the baseball in the rain and it now weighs " << this->ballWeight << " ounces" << std::endl;
    }
    double getVolume(bool isHollow);
    void addDimples(int howManyToAdd);
    void addDimplesCopy()
    {
        std::cout << "The golf ball in the coach bag started out with " << this->numberOfDimples << " dimples" << std::endl;
        this->addDimples(15);
        std::cout << "The golf ball from the coach bag now has " << this->numberOfDimples << " dimples" << std::endl;
    }
    JUCE_LEAK_DETECTOR(Ball)
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

struct BallWrapper
{
    BallWrapper(Ball* ptr) : pointerToBall( ptr ){}
    ~BallWrapper()
    {
        delete pointerToBall;
    }
    Ball* pointerToBall = nullptr;
};

struct SandballWrapper
{
    SandballWrapper(Ball::Sandball* ptr) : pointerToSandball( ptr ){}
    ~SandballWrapper()
    {
        delete pointerToSandball;
    }

    Ball::Sandball* pointerToSandball = nullptr;
};

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
    void canSwimCopy()
    {
        this->webbedFeet = true;
        std::string result;
        (this->canSwim(true)) ? result = "can swim." : result = "can't swim.";
        std::cout << "In the water the emu " << result << std::endl;
    }
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
        void migrateCopy()
        {
            this->migrate(true, 200);
            std::cout << "They let their parrot migrate for the winter and it flew " << this->migrationDistance << " miles South" << std::endl;

            this->migrate(true, 600);
            std::cout << "Philly also let their parrot migrate for the winter and it flew " << this->migrationDistance << " miles South" << std::endl;
        }
        int flapsPerTrip(int minutesPerTrip);
        void flapsPerTripCopy()
        {
            int tripA = 90;
            int tripB = 60;

            std::cout << "On a " << tripA << " minute trip a swallow flaps it's wings " << this->flapsPerTrip(tripA) << " times" << std::endl;

            std::cout << "On a " << tripB << " minute trip a swallow flaps it's wings " << this->flapsPerTrip(tripB) << " times" << std::endl;
        }
        void growWings(float growthAmount);
        JUCE_LEAK_DETECTOR(FlyingBird)
    };
    JUCE_LEAK_DETECTOR(Bird)
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

struct FlyingBirdWrapper
{
    FlyingBirdWrapper(Bird::FlyingBird* ptr) : pointerToFlyingBird( ptr ){}
    ~FlyingBirdWrapper()
    {
        delete pointerToFlyingBird;
    }
    
    Bird::FlyingBird* pointerToFlyingBird = nullptr;
};

struct BirdWrapper
{
    BirdWrapper(Bird* ptr) : pointerToBird( ptr ){}
    ~BirdWrapper()
    {
        delete pointerToBird;
    }
    Bird* pointerToBird = nullptr;
};

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
    JUCE_LEAK_DETECTOR(Zoo)
};

Zoo::~Zoo()
{
    std::cout << "The parrot's wings were " << parrot.lengthOfWings << " inches long" << std::endl;
    parrot.growWings(0.5f);
    std::cout << "Now they are " << parrot.lengthOfWings << " inches long" << std::endl;
}

struct ZooWrapper
{
    ZooWrapper(Zoo* ptr) : pointerToZoo( ptr ){}
    ~ZooWrapper()
    {
        delete pointerToZoo;
    }
    Zoo* pointerToZoo = nullptr;
};

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
    JUCE_LEAK_DETECTOR(BagOfBalls)
};

BagOfBalls::~BagOfBalls()
{
    std::cout << "The bag of balls has been destroyed" << std::endl;
}

struct BagOfBallsWrapper
{
    BagOfBallsWrapper(BagOfBalls* ptr) : pointerToBagOfBalls( ptr ){}
    ~BagOfBallsWrapper()
    {
        delete pointerToBagOfBalls;
    }
    BagOfBalls* pointerToBagOfBalls = nullptr;
};

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
    AnimalWrapper dog (new Animal());
    AnimalWrapper horse (new Animal());
    ZooWrapper bronx (new Zoo());
    ZooWrapper philly (new Zoo());
    BagOfBallsWrapper coachBag (new BagOfBalls());
    BagOfBallsWrapper practiceBag (new BagOfBalls());
    FlyingBirdWrapper swallow (new Bird::FlyingBird());
    BirdWrapper emu (new Bird());
    BallWrapper baseball (new Ball());
    SandballWrapper weightedBall (new Ball::Sandball());

    //dog.consume(2400);
    dog.pointerToAnimal->consume(2400);
    std::cout << "The animal has eaten " << dog.pointerToAnimal->totalCalories << " calories" << std::endl;

    dog.pointerToAnimal->consumeCopy();

    horse.pointerToAnimal->walk(2.1f, 60, true);
    std::cout << "The animal walked " << horse.pointerToAnimal->distanceWalked << " miles" << std::endl;

    horse.pointerToAnimal->walkCopy();

    int tripA = 90;
    int tripB = 60;
    
    std::cout << "On a " << tripA << " minute trip a swallow flaps it's wings " << swallow.pointerToFlyingBird->flapsPerTrip(tripA) << " times" << std::endl;

    std::cout << "On a " << tripB << " minute trip a swallow flaps it's wings " << swallow.pointerToFlyingBird->flapsPerTrip(tripB) << " times" << std::endl;

    swallow.pointerToFlyingBird->flapsPerTripCopy();

    emu.pointerToBird->webbedFeet = true;
    std::string result = emu.pointerToBird->canSwim(true) ? "can swim." : "can't swim.";
    std::cout << "In the water the emu " << result << std::endl;

    emu.pointerToBird->canSwimCopy();

    std::cout << "The baseball weighed " << baseball.pointerToBall->ballWeight << " ounces" << std::endl;
    baseball.pointerToBall->getHeavier(true, 2);
    std::cout << "I left the baseball in the rain and it now weighs " << baseball.pointerToBall->ballWeight << " ounces" << std::endl;

    baseball.pointerToBall->getHeavierCopy();

    std::cout << "The weighted ball was " << weightedBall.pointerToSandball->percentFilled << " percent filled" << std::endl;
    weightedBall.pointerToSandball->fillBall(10);
    std::cout << "I filled it more and it is now " << weightedBall.pointerToSandball->percentFilled << " percent filled" << std::endl;

    weightedBall.pointerToSandball->fillBallCopy();

    bronx.pointerToZoo->parrot.migrate(true, 200);
    std::cout << "They let their parrot migrate for the winter and it flew " << bronx.pointerToZoo->parrot.migrationDistance << " miles South" << std::endl;

    philly.pointerToZoo->parrot.migrate(true, 600);
    std::cout << "Philly also let their parrot migrate for the winter and it flew " << philly.pointerToZoo->parrot.migrationDistance << " miles South" << std::endl;

    bronx.pointerToZoo->parrot.migrateCopy();
    philly.pointerToZoo->parrot.migrateCopy();

    std::cout << "The golf ball in the coach bag started out with " << coachBag.pointerToBagOfBalls->golfBall.numberOfDimples << " dimples" << std::endl;
    coachBag.pointerToBagOfBalls->golfBall.addDimples(15);
    std::cout << "The golf ball from the coach bag now has " << coachBag.pointerToBagOfBalls->golfBall.numberOfDimples << " dimples" << std::endl;
    
    coachBag.pointerToBagOfBalls->golfBall.addDimplesCopy();

    std::cout << "We changed the filling in the hackySack from ";
    practiceBag.pointerToBagOfBalls->hackySack.fineSandFilling ? (std::cout << "fine sand") : (std::cout << "coarse sand");
    practiceBag.pointerToBagOfBalls->hackySack.changeFilling();
    std::cout << " to ";
    practiceBag.pointerToBagOfBalls->hackySack.fineSandFilling ? (std::cout << "fine sand\n") : (std::cout << "coarse sand\n");

    practiceBag.pointerToBagOfBalls->hackySack.changeFillingCopy();

    std::cout << "good to go!" << std::endl;
}
