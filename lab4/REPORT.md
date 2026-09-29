# Lab 4 — Group A__

> Copy this file to `lab4/REPORT.md`, fill it in, then paste the finished text into your
> pull request description. Keep the six headings exactly as they are — they are the
> marking scheme, in order. Delete this quote block and every `___` when you are done.

| | |
|---|---|
| Repository | https://github.com/durgeshkhushlani/Snake-Game-CLI |
| Base tag | `lab4-base` at commit 0bc407833019d06d14064d20623613438faf66ed |
| Pull request | https://github.com/durgeshkhushlani/Snake-Game-CLI/pull/2 |

---

## 1. Five rules — [5]

Written before opening the source. Behaviour, with an observable outcome.

| # | Rule |
|---|---|
| 1 | Eating regular food increases the score by exactly 10 points. |
| 2 | Eating special food increases the score by exactly 30 points. |
| 3 | Special food disappears if not eaten within 5 seconds of appearing. |
| 4 | The game ends when the snake's head hits a wall, an obstacle, or its own body. |
| 5 | The number of obstacles on the board increases as the score increases. |

If you could not state one of your own game's rules without going to look, say which and
why. It costs no marks.

I could not confidently state the exact obstacle-increase rate (obstacles added per how many points) without checking, since it depends on the difficulty level chosen.

---

## 2. What you could test, and what stopped you — [10]

No source changes in this part. Every `file:line` below is a line in `lab4-base`.

| # | Rule | Test written? | Blocking dependency (`file:line` + what it is) |
|---|---|---|---|
| 1 | Regular food gives 10 points | Yes | — none, `Food::value()` (snake.cpp:144-146) is public and returns 10 when `special` is false (default) |
| 2 | Special food gives 30 points | Yes | — none, `Food::special` (snake.cpp:114) is a public field on a `struct`, so it can be set directly and `value()` (snake.cpp:144-146) checked |
| 3 | Special food expires after 5s | Yes | — none, `Food::spawnTime` (snake.cpp:115) is public, so it can be backdated and `expired()` (snake.cpp:138-143) checked without waiting |
| 4 | Game ends on wall/obstacle/self collision | Partially | Self-collision half testable via `Snake::checkCollision()` (snake.cpp:104-109). Wall/obstacle half blocked: the check lives in `Game::updateGame()` (snake.cpp:284, private — class marked `private:` at snake.cpp:188), and `obstacles` (snake.cpp:152, private, no getter) can't be inspected or set from outside |
| 5 | Obstacle count increases with score | No | `Game::updateGame()` (snake.cpp:284, private) contains the milestone check (snake.cpp:324-334); `spawnObstacles()` (snake.cpp:246, private) and `obstacles`/`score` (snake.cpp:152,154, private, no getters) are all unreachable from a test |

> **Rules testable without modifying the source: 3 / 5, plus the self-collision half of rule 4 — all 4 tests pass against `lab4-base`**

"It needs user input" is not a blocking dependency. `main.cpp:214 — getch() called inside
the game loop` is.

Rule 4 and rule 5 share the same root cause: everything that touches `obstacles`, `score`, and the collision-vs-wall/obstacle logic is buried inside `Game`'s private section, with no public getter and no way to construct a `Game` in a known state. `Snake` and `Food`, by contrast, expose their state as public fields/methods, which is exactly why rules 1–3 (and half of 4) were easy and 4's other half and 5 were not.

---

## 3. Coverage, and what it missed — [6]

| | |
|---|---|
| Line coverage | 17.39% (of snake.cpp, 276 lines) |
| Branch coverage | 18.78% (of snake.cpp, 229 branches) |
| Command used | `g++ -std=c++11 -Ilab4 --coverage -O0 -g lab4/tests.cpp -o lab4/tests.exe -lgdi32` then `.\lab4\tests.exe` then `gcov -b tests.cpp` |

**One rule that is executed by the suite but not verified by it:**

| | |
|---|---|
| Rule | The snake dies when its head enters its own body (Rule 4, self-collision half) |
| Line that runs | snake.cpp:99 — `if (checkCollision(head)) return false;` runs 3 times, and on one of those calls it returns early, skipping lines 100-102 |
| The assertion that is missing | The test only checks `moved == false` (the return value). It never checks that `body` was left unchanged by the failed move — e.g. that `getBody().size()` is the same before and after, or that the head position didn't change. The state effect of the collision is exercised but never asserted on. |

---

## 4. The seam — [10]

| | |
|---|---|
| Rule made testable | The number of obstacles on the board increases as the score increases (Rule 5) |
| Commit 1 (seam) | a70a521 — Extract obstacle-milestone decision into computeObstaclesToAdd |
| Commit 2 (test) | 890ac5d — Add tests for obstacle-milestone seam (computeObstaclesToAdd) |
| Seam kind | object |
| Enabling point | The free function `computeObstaclesToAdd(int score, int &lastObstacleScore, Difficulty difficulty)`, declared at namespace scope between `Food` and `Game` (snake.cpp), instead of inline logic buried in the private `Game::updateGame()`. Any caller — including a test — can now call it directly with plain values, with no `Game` instance needed. |
| What production code gave up | Almost nothing. `Game::updateGame()` still calls the function with the same arguments and gets the same behavior; the only change is that the decision logic is no longer physically inside the class. No encapsulation was meaningfully broken, since `score`, `lastObstacleScore`, and `difficulty` were passed by reference/value rather than exposed as public members. |

The last row is graded. If the honest answer is "nothing", write that and say why the
seam cost nothing here.

The seam cost effectively nothing because the extracted function was pure decision logic with no dependency on `Game`'s other private state (snake, food, obstacles vector) — it only needed three primitive/enum values. This is exactly the kind of logic that shouldn't have been coupled to the class in the first place; pulling it out didn't weaken any invariant `Game` was protecting.

---

## 5. The double — [4]

| | |
|---|---|
| What you passed through the seam | dummy |
| The method under test | `computeObstaclesToAdd(int score, int &lastObstacleScore, Difficulty difficulty)` |

The values passed through the seam (`score`, `lastObstacleScore`, `difficulty`) are plain data, not objects with behavior — so there is no collaborator being asked a question or told to do something. `computeObstaclesToAdd` is a pure function: it reads its inputs and returns a value, with no dependency to double at all. The closest fit is "dummy" only in the loose sense that the values exist purely to satisfy the function's signature and carry no behavior of their own; a stub, spy, or mock would only apply if we were replacing an object collaborator, and this seam has none.

---

## 6. Two smells in your own tests — [5]

| | Smell | `file:line` | One-line fix |
|---|---|---|---|
| 1 | Eager test | lab4/tests.cpp:32-39 | Split into separate tests: one for the direction-reversal guard, one for growth on `move(true)`, and one specifically for the collision outcome, so a failure points at exactly one behaviour. |
| 2 | Mystery guest | lab4/tests.cpp:32-39 | Add a comment (or a local diagram) stating the snake's starting layout from `Snake::reset()` — 3 segments in a row, facing RIGHT — so the reader doesn't have to go trace `reset()` separately to see why UP→LEFT→DOWN causes a self-collision. |

Fixing them is optional. Finding them is not.

Both smells sit in the same test, "Snake dies when head enters its own body" (lab4/tests.cpp:32). It is an eager test because it silently exercises direction-reversal, two `move(true)` calls, and the collision path in one function with a single assertion at the end — a failure would require re-reading the whole test to know which step broke. It is also a mystery guest because its correctness depends on `Snake`'s default starting body (set inside `Snake::reset()`, snake.cpp:66-73) which is never shown or restated in the test itself.

___