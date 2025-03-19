Towers:
    Attributes:
        level - the towers current level which starts at 1 when first bought
        buyingCost - the amount needed to buy the tower and also serves as the upgrade cost
        refundValue - amount given back when the tower is sold
        range - how far the tower can recognize and reach the enemies
        power - how much hp the tower deals to critters per hit
        rateOfFire - in milliseconds, how often the tower shoots
        type - only three types of towers so far which are archer, ballista and catapult
        position - where the tower is located with x and y coordinates

    Towers Constructors
        There are two Constructors.

        The first constructor contains all of the classe's attribute and normally shouldn't be used in the Driver.

        The second constructor only needs a type and a position. This is the constructor to use in the Driver. Depending
        on the type entered, the tower's stats will be automatically set to the appropriate amount.

    shoot(Critter& critter)
        deducts the tower's power from the critter's health. If the critter's position is too far from the tower's range,
        it will not hit the critter.

    levelUp(double& balance)   
        Takes money from the balance equal to the tower's buyingCost. Then, depending on the tower's type, it will increase
        the tower's stats differently. 

    Contains Getters and Setters for all of the attributes.