# First Person Adventure (Unreal Engine)
[Русский (README.ru.md)](./README.ru.md)

Learning project based on Epic’s official tutorial  
**[Code a First-Person Adventure Game in Unreal Engine](https://dev.epicgames.com/documentation/unreal-engine/code-a-firstperson-adventure-game-in-unreal-engine?lang=en-US)**  
(Unreal Engine **5.8.x**).

This repo follows that guide and extends it with a small in-game UI, settings, and localization.


## What’s included
### From the tutorial
- First-person adventure gameplay flow as in the official Epic guide
- Project sources under `AdventureGame/`

### Extra features
- **Pause menu (Tab)** — pauses the game and opens a menu overlay
- **Settings**
  - Interface language: **English** / **Russian**
  - Overall **graphics quality** (scalability)
- **Localized UI strings** (String Tables + Localization Dashboard / `.locres`)
- **Matte / frosted-style** menu presentation (shared menu shell + content widgets)

### Releases
- Large binaries (**> 10 MB**) are **not** stored in git history
- They are published via **[assetout](https://github.com/ambientneon/assetout)** to **GitHub Releases**
- The same release also includes a **Shipping** Windows build of the game (no debug files intended)


## Repository layout
```text
.
├── AdventureGame/     # Unreal project (code, content, config)
├── ue-build/          # Local package output (ignored by git; optional)
├── README.md
├── README.ru.md
└── .gitignore
```

Exact assetout metadata/paths may vary; see the [assetout](https://github.com/ambientneon/assetout) docs for this repo’s setup.


## Requirements
- **Unreal Engine 5.8.x** (project was developed on 5.8.2)
- Visual Studio 2022 (with C++ game development workload, project was developed on VSC 2026) on Windows
- Git
- [assetout](https://github.com/ambientneon/assetout) — to fetch large binaries from Releases


## Clone & restore binaries
### 1. Clone the repository
```bash
git clone https://github.com/ambientneon/ue-tutor-fpag.git
cd ue-tutor-fpag


### 2. Sync large files with assetout
Binaries over ~10 MB live in **GitHub Releases**, not in the git tree.  
Install and use **assetout** as described upstream:

**https://github.com/ambientneon/assetout**

Typical flow (see assetout README for exact commands):

```bash
# install assetout (example — use the method from upstream docs)
# then, from the repo root:
assetout pull
```

After a successful sync, editor binaries / content expected by the project should be present locally.

> If you only want to **play** the packaged game, download the Shipping zip from **Releases** — you do not need to build from source.


## Open & build from source
1. Sync binaries with assetout (above)
2. Open `AdventureGame/AdventureGame.uproject` (or your `.uproject` name)
3. Build the editor target when prompted
4. Play in editor; for localization checks prefer **Standalone Game**

### Packaging (Shipping)
High-level checklist used for the public build:
- Localization target compiled for **en** and **ru-RU**
- Packaging: cultures **en**, **ru-RU**; internationalization support enabled
- Stage localization data (e.g. `Localization/Game`)
- **Always Cook** the String Tables folder (do **not** rely on a Primary Asset type for `UStringTable` alone)
- Package **Shipping**, strip/omit `.pdb` when uploading

Details may evolve; if UI text is missing in Shipping, verify `.locres` and String Tables are in the staged build.


## Playing the release build
1. Open **GitHub → Releases**
2. Download the Windows Shipping archive attached to the release
3. Extract and run the `.exe`

Notes:
- Windows SmartScreen may warn about an **unsigned** build
- Language and graphics can be changed from the in-game settings (Tab → Settings)


## Controls (high level)
| Input | Action |
|--------|--------|
| **Tab** | Toggle pause / main menu |
| WASD + mouse | Movement / look (tutorial defaults) |
| Menu UI | Navigate settings, confirm/cancel |

Exact bindings follow the project’s Enhanced Input setup.


## Localization
- UI text uses **String Tables** + UE localization pipeline
- Runtime language switch via game settings (culture codes such as `en`, `ru-RU`)
- Shipping builds must include cooked String Tables and staged `.locres` files


## Contributing / feedback
This is primarily a **learning / tutorial** repository.  
Issues and suggestions are welcome via GitHub Issues.


## License & third parties
- Tutorial content and engine usage subject to **Epic Games** terms and the Unreal Engine EULA
- [assetout](https://github.com/ambientneon/assetout) — see that project’s license


## Links
- [Epic tutorial — First-Person Adventure](https://dev.epicgames.com/documentation/unreal-engine/code-a-firstperson-adventure-game-in-unreal-engine?lang=en-US)
- [assetout](https://github.com/ambientneon/assetout)
- [Unreal Engine documentation](https://dev.epicgames.com/documentation/unreal-engine/)