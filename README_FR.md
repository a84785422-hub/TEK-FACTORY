# TEK FACTORY — VST3 Jumpstyle / Tekstyle

Première base de plugin instrument pour Windows x64 / FL Studio. Interface noire, violet fluorescent et vert acide. Les 30 variations sont intégrées dans le binaire : aucune dépendance aux fichiers Samples après compilation.

## Fonctions incluses

- 30 samples intégrés : 10 variations déterministes de chacune des 3 références fournies.
- Sélecteur manuel de kick et bouton de pré-écoute.
- Déclenchement MIDI (jouer une note dans le Piano Roll / clavier MIDI).
- Pitch, EQ low/mid/high, Drive, Clip, Sub, Crush, Punch, Length et Output.
- Sauvegarde/rappel des paramètres via l'état du plugin.
- Format VST3 et build Standalone via JUCE/CMake.

## Important sur les variations

Les fichiers `_01` à `_10` sont des rendus audio transformés à partir de chaque kick source (pitch, filtrage, enveloppe et non-linéarités différentes). Ils ont des traitements distincts, mais ne prétendent pas être des enregistrements complètement indépendants. Les fichiers `*_SOURCE.wav` sont des copies de référence normalisées. Consulte `AUDIO_ANALYSIS.txt` pour les mesures techniques des trois fichiers d'origine.

## Compilation Windows sans installer Visual Studio sur ton PC

1. Crée un dépôt GitHub vide nommé `TEK-FACTORY`.
2. Envoie le contenu de ce dossier à la racine du dépôt, y compris le dossier caché `.github`.
3. Ouvre l'onglet **Actions**, puis le workflow **Build TEK FACTORY VST3**.
4. Clique **Run workflow** et attends que le job soit vert.
5. Dans le résultat du job, télécharge l'artifact `TEK-FACTORY-Windows-x64`.
6. Décompresse le ZIP. Copie `TEK FACTORY.vst3` dans `C:\Program Files\Common Files\VST3\` (droits administrateur éventuellement nécessaires).
7. Dans FL Studio : **Options > Manage plugins > Find installed plugins**. Charge TEK FACTORY comme instrument et joue des notes MIDI. Le bouton FIRE KICK sert à la pré-écoute dans l'interface.

Le workflow télécharge JUCE 8.0.10 et compile avec les outils Visual Studio du runner GitHub. Le premier build peut prendre plusieurs minutes.

## Compilation locale (facultatif)

Nécessite CMake 3.22+ et Visual Studio 2022 avec le workload C++ Desktop. Dans un terminal Developer PowerShell :

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release --target TEK_FACTORY_VST3 TEK_FACTORY_Standalone
```

## État / limites de cette version

C'est une base fonctionnelle à compiler et tester : le binaire VST3 n'est pas fourni ici comme s'il avait été compilé. Le workflow génère le binaire. Le pitch utilise un changement de vitesse de lecture (donc la durée change aussi). EQ et autres paramètres sont manuels. Pas de génération aléatoire, conformément au choix demandé. Le MIDI déclenche le kick; le bouton de pré-écoute est disponible dans l'interface.

## Licences

JUCE est utilisé comme dépendance externe sous sa licence applicable. Vérifie les conditions de licence JUCE et de redistribution avant toute distribution commerciale du plugin.
