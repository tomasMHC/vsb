# Cvičení 1


Cílem cvičení bude implementovat průchod bludištěm, a to pomocí čtyř různých variant reprezentace scény.

1. **Založte nový projekt typu konzolová aplikace** ve vámi zvoleném IDE a seznamte se s adresářovou strukturou projektu.

2. **Implementace pomocí zanořených polí**

	1. Vytvořte třídu **JaggedArray** a v ní metodu **Run**, která bude sloužit jako vstupní bod pro spuštění dané implementace. V rámci metody **Run** pole hodnot, které bude reprezentovat hrací plochu. Na hrací ploše budou např. následující typy objektů (zeď, figurka, prázdné pole).
	2. Vytvořte metodu na načtení mapy z přiloženého souboru (1=zeď, 0=volno).
	3. Vytvořte metodu, která přidá figurku na nějaké prázné pole mapy (parametry souřadnice **X** a **Y** pozice), Metody použijte v metodě **Run**.
	4. Implementujte metodu **MainLoop**, která bude přijímat jako parametr naše dvojrozměrné pole. V rámci metody implementujte kód, který na základě předaného pole provede vykreslení scény do konzole. Vykreslujte pomocí znaku Unicode **\u2588** (jedná se o obdélník – čtverec získáte vykreslením dvou těchto znaků vedle sebe). Metodu **MainLoop** následně zavolejte z metody **Run** a ověřte, že vykreslení funguje. Při implementaci využijte metody a vlastnosti `Console.Clear`, `Console.SetCursorPosition`, `Console.ForegroundColor`, `Console.BackgroundColor` a `Console.CursorVisible`.
	5. V rámci metody **Run** spusťte metodu **MainLoop** v nekonečné smyčce. Po každém zavolání metody **MainLoop** spusťte následující kód: `Thread.Sleep(1000);`
	6. V rámci metody **MainLoop** implementujte posun figutky (při každém zavolání metody dojde k posunu na libovolné sousední volné pole).

3. **Implementace pomocí pole tříd**

	1. Zkuste si vytvořit více typů figure (jako např. Pac-Man)
	2. Vše vhodně přepište na třídy.

----

## Volitelná část

5. **Implementace pomocí vícerozměrného pole**

   1. Vytvořte třídu **MultidimensionalArray**, která bude reprezentovat danou implementaci.
   2. Implementujte identickou logiku jako v bodě 2., ale tentokrát s využitím vícerozměrných polí.
   

6. **Implementace pomocí pole struktur**

   1. Vytvořte třídu **StructureArray**, která bude reprezentovat danou implementaci.
   2. Implementujte identickou logiku jako v bodě 3., ale tentokrát s využitím struktur.

----

## Pomůcka

```csharp
private static void clearConsole()
{
    Console.Clear();

    //\x1b[2J smaže viditelnou plochu obrazovky
    //\x1b[3J smaže scrollback buffer
    //\x1b[H posune kurzor na domovskou pozici
    Console.Write("\x1b[3J\x1b[H\x1b[2J");

    Console.SetCursorPosition(0, 0);
    Console.ForegroundColor = ConsoleColor.Red;
    Console.BackgroundColor = ConsoleColor.Black;
}
```