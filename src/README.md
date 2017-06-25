# README - Instalation #

# Kalendář pro plánování - Zadání #

Organizace sociálních událostí je složitou záležitostí, protože účastníci mají často nabité dny, a těžko se pak hledají možné termíny. To je třeba usnadnit.

## Implementujte následující funkcionalitu ##


* Zadávání aktivit uživatele (podpora opakování, omezeného opakování)
* Sdílení kalendářů mezi uživateli
* Vyhledávání nejbližších možných termínů (možnost přesouvat vybrané události)
* Export do formátu iCalendar


## Nástroj musí dále splňovat následující funkcionality: ##


* Podpora různých aktivit (povinné, volitelné, přesouvatelné)
* Sdílené, veřejné a soukromé události
* Vyhledávání termínů - nejbližší možný, nejbližší dostatečný s maximálně x přesuny
* Podpora zdravého životního stylu (kontrola pravidelných pauz na oběd, snídani, večeři, svačinu)


## Kde lze využít polymorfismus? (doporučené) ##


* Položky v kalendáři
* Přístupy do kalendáře
* Export

# Instalace #

Aplikace využívá databázi MySQL. MySQL konstanty pro připojení k databázi je možné nakonfigurovat v src/Service/MySQL/Connector.h. V adresáři examples se proto nachází soubor plan_calendar.sql, který vytvoří potřebné tabulky pro práci nebo soubor test_data.sql, který obsahuje již předpřipravená testovací data.
