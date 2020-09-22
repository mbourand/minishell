[![Codacy Badge](https://app.codacy.com/project/badge/Grade/24fe71c09a0b4531b97dc0a0cc690c5c)](https://www.codacy.com/manual/nforay/minishell?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=nforay/minishell&amp;utm_campaign=Badge_Grade)

Projet réalisé avec [@nforay]( https://github.com/nforay )

# minishell
L’objectif de ce projet est de créer un simple shell. Ca sera votre propre petit bash, ou zsh. Vous en apprendrez beaucoup sur les process et les file descriptors.

## Utilisation
Le programme se compile avec ``make`` et se lance avec ``./minishell``

 ## Features :
- Les opérateurs ``;`` et ``|``
- Les guillemets ``'`` et ``"``
- Les variables d'environnement (ex : ``$PATH`` ou ``"$PATH"``)
- La variable ``$?`` et ``$SHLVL`` (pas complètement testée)
- Les builtins ``cd``, ``echo [-n]``, ``export``, ``unset``, ``pwd``, ``env``, ``exit``
- Les redirections ``>>``, ``<`` et ``>`` **avec ou sans numéro de fd** devant, les redirections tu type ``n>&m`` ne marchent pas
- Les signaux ``SIGINT (CTRL+C)`` et ``SIGQUIT (CTRL+\)``
- ``End of transmission (CTRL+D)`` (le fonctionnement diffère de bash dans certains cas)
- L'exécution de commande en chemin absolu, relatif, ou juste avec le nom de l'exécutable (basé sur ``$PATH``)

## Preview
Soon™️
