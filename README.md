# UE Gladiators of the Forest
UE Gladiators of the Forest is a spectator game in which two AI controlled gladiators fight each other to death. I developed this project to demonstrate my knowledge of Behaviour Trees in Unreal 5. 

![ProjectDemostration](https://github.com/mariofv/UEGladiatorsOfTheForest/blob/develop/Media/gameplay.png)

## Installing
Download the build files contained in the .zip from [the lastest release](https://github.com/mariofv/UEGladiatorsOfTheForest/releases/tag/v1.0) and execute `UEGladiatorsOfTheForest.exe`.

## Editing
If you want to edit the project / examine the setup in the editor please clone this repo in your machine and import it to Unreal Engine 5.0.3.

## Project Structure
- The folder `Content\UEGladiators` contains the different Blueprints, objects and assets used in this project.
- The Blueprint `BP_Gladiator` contains logic for the AI controlled pawn.
- The Blueprint `BP_Weapon` inherits from the C++ class `AWeapon`, which defines the logic for the main weapon system.
- The Blueprint `BP_Ranged_AI_Controller` defines the AI Controllers of the different gladiators.
- This AI uses the behaviour tree `BP_Ranged_Gladiator_BT`. 

## AI Clarifications
- Almost all the behaviour tree tasks hve been developed in Blueprints.
- There are two exceptions to this: the `Aim Task` and the `Clear Focus Task`.
- The `Aim Task` has a Blueprint implementation in `BP_Aim_Target_Task` and a C++ implementation in the class `UBTTaskAimTarget`. The behaviour tree uses the later.
- The `Clear Focus Task` has a C++ implementation in `UBTTaskClearFocus`.
- The reason for just having only two tasks implemented in C++ is that the project was built on top of a base project that is purely Blueprints.
- Because of this is really difficult to call Blueprint defined methods from C++, and some stuff was redeclared like the `RotationMode` for the `SetRotationMode` method.
- A solution for this problem would be reimplementing hte project on top of a base project that uses C++, like [this one](https://github.com/dyanikoglu/ALS-Community).
   
## Built With
* [Advanced Locomotion System V4](https://www.unrealengine.com/marketplace/en-US/product/advanced-locomotion-system-v1) - Used as a base project for the diferent animations.
* [Realistic Starter VFX Pack Vol 2](https://www.unrealengine.com/marketplace/en-US/item/f489377b0596412fb8806f50b1ae5d8d) - Used for different VFXs.

## License
This project is licensed under the MIT License - see the [LICENSE](https://github.com/mariofv/UEGladiatorsOfTheForest/blob/develop/LICENSE) file for details.
