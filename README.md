# CAGD-380 Final Project: Gauntlet Clone

[Class Map](https://lucid.app/lucidchart/75200c95-1958-46fa-8a13-f5200a18a324/edit?view_items=7iz8NGrL_qWN&invitationId=inv_826e87f0-177e-465a-9c82-ce5d1350cc24)

## Game Overview
- Code will need to be compiled on opening the project. Also, BP_CameraManager had a bad habit of losing its parent class reference on reload no matter how many times it was fixed, saved/compiled, and commited; if it gives you trouble, right click and reload it. 
- When testing gameplay, please start in the CharacterSelection level. It has not been set as the default level when opening the project in the editor because doing so would revert the designated game mode and corrupt some of the UI nodes; all in all, it's just easier to switch to CharacterSelection after the initial load and compile.

## Team Roles
- Logan: Combat systems, attacks, damage, enemies, enemy spawners
- Kendal: Multiplayer and scene transition logic, player movement, level design, UI
