# Nebula Salvage

Учебный проект на C++ для освоения идиоматичного и производительного кода в контексте геймдева. Ты пишешь **тонкий игровой фреймворк** поверх простого CG-движка и собираешь из него 2D top-down аркаду.

Темы для изучения перечислены в [plan.md](plan.md). Пошаговый список задач — в [ROADMAP.md](ROADMAP.md).

## Суть игры

**Nebula Salvage** — top-down аркада:

- Корабль игрока летает, собирает обломки, уклоняется от врагов
- Волны врагов, апгрейды между волнами
- Частицы (взрывы, двигатель), простой UI (HP, счёт)
- Асинхронная подгрузка текстур и звуков между волнами
- Сохранение прогресса и настроек на диск

Игровой цикл: `меню → волна → апгрейд → волна → game over → таблица рекордов`.

## Почему Raylib

| Движок | Плюсы для обучения |
|--------|-------------------|
| **Raylib** (рекомендуется) | Минимум бойлерплейта, C API → отлично тренирует RAII-обёртки, быстрый результат |
| SFML | Уже «C++-ный», меньше поводов писать свои обёртки |
| SDL2 | Индустриальный стандарт, но больше шума на старте |

Raylib даёт рендер, ввод, звук и таймер — фокус остаётся на **C++**, а не на графическом пайплайне.

## Архитектура

```
┌─────────────────────────────────────┐
│  Game (Nebula Salvage)              │  ← геймплей, волны, баланс
├─────────────────────────────────────┤
│  Engine Core (твой C++ фреймворк)   │  ← ECS, ресурсы, события, пулы
├─────────────────────────────────────┤
│  Platform Wrappers (RAII)           │  ← Texture, Sound, Window...
├─────────────────────────────────────┤
│  Raylib (C API)                     │
└─────────────────────────────────────┘
```

## Структура репозитория

```
nebula_salvage/
├── cmake/
├── external/raylib/
├── src/
│   ├── platform/       # RAII-обёртки Raylib
│   ├── core/           # Entity, Component, EventBus, ResourceManager
│   ├── systems/        # Movement, Collision, Render, Particle, AI
│   ├── game/           # WaveManager, UpgradeShop, SaveGame
│   └── main.cpp
├── assets/             # спрайты, звуки, levels.json
├── tests/              # Catch2
└── benchmarks/         # Google Benchmark
```

## Фазы разработки

| Фаза | Содержание | Ключевые темы из plan.md |
|------|------------|--------------------------|
| 0 | Каркас проекта | инструменты, chrono, assert |
| 1 | Platform Wrappers | RAII, rule of five, move, copy-and-swap, PIMPL |
| 2 | ResourceManager | контейнеры, filesystem, optional, smart pointers |
| 3 | ECS | type erasure, CRTP, concepts, STL-алгоритмы |
| 4 | Геймплей | variant, лямбды, NVI, SoA, spatial hash |
| 5 | Частицы и пулы | placement new, constexpr LUT, бенчмарки |
| 6 | Волны и апгрейды | structured bindings, fold, ranges |
| 7 | Асинхронность | jthread, atomics, futures, coroutines |
| 8 | Сохранения | filesystem, format, variadic templates, traits |
| 9 | Полировка | тесты, санитайзеры, модули (опционально) |

## Минимальный MVP

1. RAII-обёртки + окно + спрайт игрока
2. Движение WASD + 5 врагов-преследователей
3. AABB-коллизии + HP
4. 100 частиц взрыва через object pool
5. Счёт и game over

Остальное добавляется итеративно по [ROADMAP.md](ROADMAP.md).

## Критерии усвоения темы

Для каждой фазы полезно ответить себе:

- Почему здесь `unique_ptr`, а не `shared_ptr`?
- Что сломается, если убрать `noexcept` у move-конструктора вектора частиц?
- Профилировщик показывает — стоит ли SoA-переход для 500 сущностей?
- Thread Sanitizer молчит после async-загрузки?

## Соответствие тем plan.md и кода

| Раздел plan.md | Место в проекте |
|----------------|-----------------|
| RAII, rule of five | `platform/Texture`, `Sound`, `Window` |
| Smart pointers | `ResourceManager`, ownership сущностей |
| Move semantics | move-конструкторы обёрток, `vector<unique_ptr<Entity>>` |
| optional / variant / any | загрузка ресурсов, AI-компоненты, type-erased storage |
| constexpr | LUT тригонометрии, compile-time константы баланса |
| Concepts | `template<Component T>`, `Hashable` для spatial grid |
| Ranges | фильтрация сущностей, pipeline в debug UI |
| CRTP | `SystemBase<Derived>` со static polymorphism |
| PIMPL | `Renderer`, `AudioEngine` |
| NVI | `System::update()` → private virtual `do_update()` |
| Type erasure | `Event`, `ComponentStorage` |
| Policy-based design | `ComponentArray` vs `SparseSet` |
| STL containers / algorithms | везде; отдельно — spatial hash |
| string_view / span | пути к ассетам, collision arrays |
| chrono / filesystem / format | game loop, saves, logging |
| SoA, pools, cache locality | particles, transforms |
| Threading / atomics / futures | async asset loading |
| Coroutines | procedural wave generator |
| Templates, traits, fold | serializer, component storage |
| Placement new | object pool |
| copy-and-swap | все копируемые/перемещаемые ресурсы |
| Tests / sanitizers / benchmarks | `tests/`, `benchmarks/` |
