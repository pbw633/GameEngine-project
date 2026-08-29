
    Return types - when to use &:

    Primitive / small types:
        int              -> int
        float            -> float
        bool             -> bool
        small struct     -> value
        sf::Vector2f     -> value
        sf::Color        -> value

    Existing larger objects:
        Read only        -> const T&
        Can be modified  -> T&

    New object that caller should own:
        -> T

    Rule of thumb:
        Use & when returning a reference to an EXISTING object.
        Do NOT use & just to avoid copies of small values.

    Examples:
        int getRows() const;
        float getRadius() const;
        bool isWall() const;

        const std::vector<Tile>& getGrid() const;
        std::vector<Tile>& getGrid();

        const Tile& getTile(...) const;
        Tile& getTile(...);
