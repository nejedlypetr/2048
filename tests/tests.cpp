#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../headers/game.hpp"

class GameTester : public Game {
public:
    using Game::Game;  // Inherit constructors

    // Expose private methods for testing
    using Game::moveLeft;
    using Game::moveRight;
    using Game::moveUp;
    using Game::moveDown;

    // Expose private variables for testing
    using Game::board;
    using Game::size;
};

TEST_CASE("Move Left Tests", "[move-left]") {
    SECTION("Move Left Test 1") {
        GameTester sut({
           {0, 0, 0, 2},
           {0, 0, 0, 2},
           {0, 0, 0, 2},
           {0, 0, 0, 2}
        });
        sut.moveLeft();
        REQUIRE_THAT(sut.board,
         Catch::Equals(std::vector<std::vector<size_t>>{
             {2, 0, 0, 0},
             {2, 0, 0, 0},
             {2, 0, 0, 0},
             {2, 0, 0, 0}
         })
        );
    }

    SECTION("Move Left Test 2") {
        GameTester sut({
                               {2, 0, 0, 0},
                               {0, 2, 0, 0},
                               {0, 0, 2, 0},
                               {0, 0, 0, 2}
                       });
        sut.moveLeft();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {2, 0, 0, 0},
                             {2, 0, 0, 0},
                             {2, 0, 0, 0},
                             {2, 0, 0, 0}
                     })
        );
    }

    SECTION("Move Left Test 3") {
        GameTester sut({
                               {0, 0, 0, 2},
                               {0, 0, 2, 0},
                               {0, 2, 0, 0},
                               {2, 0, 0, 0}
                       });
        sut.moveLeft();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {2, 0, 0, 0},
                             {2, 0, 0, 0},
                             {2, 0, 0, 0},
                             {2, 0, 0, 0}
                     })
        );
    }

    SECTION("Move Left Test 4") {
        GameTester sut({
                               {2, 0, 0, 2},
                               {2, 0, 0, 2},
                               {2, 0, 0, 2},
                               {2, 0, 0, 2}
                       });
        sut.moveLeft();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {4, 0, 0, 0},
                             {4, 0, 0, 0},
                             {4, 0, 0, 0},
                             {4, 0, 0, 0}
                     })
        );
    }

    SECTION("Move Left Test 5") {
        GameTester sut({
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2}
                       });
        sut.moveLeft();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {4, 4, 0, 0},
                             {4, 4, 0, 0},
                             {4, 4, 0, 0},
                             {4, 4, 0, 0}
                     })
        );
    }

}

TEST_CASE("Move Right Tests", "[move-right]") {
    SECTION("Move Right Test 1") {
        GameTester sut({
                               {2, 0, 0, 0},
                               {2, 0, 0, 0},
                               {2, 0, 0, 0},
                               {2, 0, 0, 0}
                       });
        sut.moveRight();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 2},
                             {0, 0, 0, 2},
                             {0, 0, 0, 2},
                             {0, 0, 0, 2}
                     })
        );
    }


    SECTION("Move Right Test 2") {
        GameTester sut({
                               {2, 0, 0, 0},
                               {0, 2, 0, 0},
                               {0, 0, 2, 0},
                               {0, 0, 0, 2}
                       });
        sut.moveRight();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 2},
                             {0, 0, 0, 2},
                             {0, 0, 0, 2},
                             {0, 0, 0, 2}
                     })
        );
    }

    SECTION("Move Right Test 3") {
        GameTester sut({
                               {0, 0, 0, 2},
                               {0, 0, 2, 0},
                               {0, 2, 0, 0},
                               {2, 0, 0, 0}
                       });
        sut.moveRight();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 2},
                             {0, 0, 0, 2},
                             {0, 0, 0, 2},
                             {0, 0, 0, 2}
                     })
        );
    }

    SECTION("Move Right Test 4") {
        GameTester sut({
                               {2, 0, 0, 2},
                               {2, 0, 0, 2},
                               {2, 0, 0, 2},
                               {2, 0, 0, 2}
                       });
        sut.moveRight();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 4},
                             {0, 0, 0, 4},
                             {0, 0, 0, 4},
                             {0, 0, 0, 4}
                     })
        );
    }

    SECTION("Move Right Test 5") {
        GameTester sut({
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2}
                       });
        sut.moveRight();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 4, 4},
                             {0, 0, 4, 4},
                             {0, 0, 4, 4},
                             {0, 0, 4, 4}
                     })
        );
    }
}

TEST_CASE("Move Up Tests", "[move-up]") {
    SECTION("Move Up Test 1") {
        GameTester sut({
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {2, 2, 2, 2}
                       });
        sut.moveUp();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {2, 2, 2, 2},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}
                     })
        );
    }


    SECTION("Move Up Test 2") {
        GameTester sut({
                               {2, 0, 0, 0},
                               {0, 2, 0, 0},
                               {0, 0, 2, 0},
                               {0, 0, 0, 2}
                       });
        sut.moveUp();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {2, 2, 2, 2},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}
                     })
        );
    }

    SECTION("Move Up Test 3") {
        GameTester sut({
                               {0, 0, 0, 2},
                               {0, 0, 2, 0},
                               {0, 2, 0, 0},
                               {2, 0, 0, 0}
                       });
        sut.moveUp();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {2, 2, 2, 2},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}
                     })
        );
    }

    SECTION("Move Up Test 4") {
        GameTester sut({
                               {2, 2, 2, 2},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {2, 2, 2, 2}
                       });
        sut.moveUp();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {4, 4, 4, 4},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}
                     })
        );
    }

    SECTION("Move Up Test 5") {
        GameTester sut({
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2}
                       });
        sut.moveUp();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {4, 4, 4, 4},
                             {4, 4, 4, 4},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}
                     })
        );
    }
}

TEST_CASE("Move Down Tests", "[move-down]") {
    SECTION("Move Down Test 1") {
        GameTester sut({
                               {2, 2, 2, 2},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0}
                       });
        sut.moveDown();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {2, 2, 2, 2}
                     })
        );
    }


    SECTION("Move Down Test 2") {
        GameTester sut({
                               {2, 0, 0, 0},
                               {0, 2, 0, 0},
                               {0, 0, 2, 0},
                               {0, 0, 0, 2}
                       });
        sut.moveDown();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {2, 2, 2, 2}
                     })
        );
    }

    SECTION("Move Down Test 3") {
        GameTester sut({
                               {0, 0, 0, 2},
                               {0, 0, 2, 0},
                               {0, 2, 0, 0},
                               {2, 0, 0, 0}
                       });
        sut.moveDown();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {2, 2, 2, 2}
                     })
        );
    }

    SECTION("Move Down Test 4") {
        GameTester sut({
                               {2, 2, 2, 2},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {2, 2, 2, 2}
                       });
        sut.moveDown();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {4, 4, 4, 4},
                     })
        );
    }

    SECTION("Move Down Test 5") {
        GameTester sut({
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2}
                       });
        sut.moveDown();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {4, 4, 4, 4},
                             {4, 4, 4, 4}
                     })
        );
    }
}

TEST_CASE("Move All Directions Tests", "[move-all-directions]") {
    SECTION("Move All Directions Test 1") {
        GameTester sut({
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {0, 0, 0, 0},
                               {2, 2, 2, 2}
                       });
        sut.moveUp();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {2, 2, 2, 2},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}
                     })
        );
        sut.moveRight();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 4, 4},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}
                     })
        );
        sut.moveDown();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 4, 4}
                     })
        );
        sut.moveLeft();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {8, 0, 0, 0}
                     })
        );
    }


    SECTION("Move All Directions Test 2") {
        GameTester sut({
                               {2, 0, 0, 2},
                               {0, 2, 2, 0},
                               {0, 2, 2, 0},
                               {2, 0, 0, 2}
                       });
        sut.moveDown();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {4, 4, 4, 4}
                     })
        );
        sut.moveLeft();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {8, 8, 0, 0}
                     })
        );
        sut.moveUp();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {8, 8, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}
                     })
        );
        sut.moveRight();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 16},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0}
                     })
        );
    }

    SECTION("Move All Directions Test 3") {
        GameTester sut({
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2},
                               {2, 2, 2, 2}
                       });
        sut.moveDown();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {4, 4, 4, 4},
                             {4, 4, 4, 4}
                     })
        );
        sut.moveDown();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {8, 8, 8, 8}
                     })
        );
        sut.moveLeft();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {16, 16, 0, 0}
                     })
        );
        sut.moveRight();
        REQUIRE_THAT(sut.board,
                     Catch::Equals(std::vector<std::vector<size_t>>{
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 0},
                             {0, 0, 0, 32}
                     })
        );
    }
}
