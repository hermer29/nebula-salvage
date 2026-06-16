# ROADMAP — Nebula Salvage

Одна строка = одна задача. Выполняй сверху вниз.

## Фаза 0 — Каркас проекта

- [x] Создать структуру каталогов проекта (`src/`, `assets/`, `tests/`, `benchmarks/`, `cmake/`)
- [x] Настроить CMake с C++20 и подключить Raylib через FetchContent
- [x] Включить флаги компилятора: `-Wall -Wextra -Wpedantic -Werror`
- [x] Добавить опциональные санитайзеры (Address, Undefined, Thread) в CMake
- [x] Настроить `clang-format` и базовый `.clang-tidy`
- [x] Реализовать `main.cpp` с инициализацией окна Raylib
- [x] Реализовать игровой цикл с измерением delta time через `std::chrono`
- [x] Добавить `assert` для инвариантов игрового цикла (delta time > 0, окно открыто)
- [x] Вывести FPS и delta time в заголовок окна или debug-оверлей

## Фаза 1 — Platform Wrappers (RAII)

- [ ] Создать класс `Window` с RAII-владением окном Raylib
- [ ] Создать класс `Texture`: загрузка из `std::string_view`, освобождение в деструкторе
- [ ] Запретить копирование `Texture`, реализовать move-конструктор с `noexcept`
- [ ] Реализовать оператор присваивания `Texture` через copy-and-swap
- [ ] Создать класс `Sound` по тому же паттерну (rule of five)
- [ ] Создать класс `Music` с управлением воспроизведением (play/stop)
- [ ] Создать класс `Font` с RAII-владением шрифтом
- [ ] Добавить фабричные функции `make_texture()`, `make_sound()` вместо голых `new`
- [ ] Вернуть `std::optional<Texture>` из загрузчика при ошибке чтения файла
- [ ] Применить PIMPL к классу `Renderer` для скрытия деталей отрисовки
- [ ] Отрисовать спрайт игрока через `Texture` на экране

## Фаза 2 — ResourceManager

- [ ] Реализовать `ResourceManager` с кешем `std::unordered_map<std::string, Texture>`
- [ ] Добавить метод `load<Texture>(std::string_view path)` с возвратом ссылки на кешированный ресурс
- [ ] Хранить владеемые ресурсы через `std::unique_ptr` внутри менеджера
- [ ] Создать `assets/manifest.json` со списком текстур и звуков
- [ ] Парсить manifest через `std::filesystem` и `std::ifstream`
- [ ] Парсить числовые поля конфига через `std::from_chars`
- [ ] Вернуть `std::expected<T, LoadError>` (или `std::optional`) при ошибке загрузки
- [ ] Добавить hot-reload: перечитать manifest по клавише (debug)
- [ ] Написать unit-тест: повторный `load()` возвращает тот же объект
- [ ] Написать unit-тест: загрузка несуществующего файла возвращает ошибку

## Фаза 3 — Entity-Component-System

- [ ] Определить тип `EntityId` (uint32_t) и генератор ID
- [ ] Создать компонент `Transform` (позиция, поворот, масштаб)
- [ ] Создать компонент `Sprite` (ссылка на текстуру, тинт)
- [ ] Создать компонент `Velocity` (скорость, угловая скорость)
- [ ] Создать компонент `Health` (current, max)
- [ ] Реализовать `ComponentArray<T>` на `std::vector` + `unordered_map<EntityId, size_t>`
- [ ] Добавить concept `Component` с ограничениями на типы компонентов
- [ ] Реализовать альтернативный storage через type erasure (`std::any` или своя vtable)
- [ ] Создать `EntityManager`: create / destroy сущности
- [ ] Реализовать `System` с NVI: публичный `update()` вызывает private virtual `do_update()`
- [ ] Реализовать CRTP-базу `SystemBase<Derived>` для static polymorphism
- [ ] Реализовать `RenderSystem`: обход сущностей с `Transform` + `Sprite`
- [ ] Реализовать `MovementSystem`: обновление позиций из `Velocity`
- [ ] Использовать `remove_if` + `erase` для удаления мёртвых сущностей
- [ ] Написать unit-тест: destroy сущности освобождает слот в component array

## Фаза 4 — Геймплей: игрок, враги, коллизии

- [ ] Реализовать управление игроком (WASD) с изменением `Velocity`
- [ ] Ограничить игрока границами экрана
- [ ] Создать компонент `PlayerTag` и `EnemyTag`
- [ ] Реализовать AI `ChaserAI` (преследование игрока)
- [ ] Реализовать AI `DrifterAI` (случайное блуждание)
- [ ] Реализовать AI `KamikazeAI` (разгон к игроку)
- [ ] Хранить AI в `std::variant<ChaserAI, DrifterAI, KamikazeAI>`
- [ ] Обновлять AI через `std::visit` с лямбдами (явный захват)
- [ ] Реализовать `SpatialHash` для broad-phase коллизий
- [ ] Реализовать narrow-phase AABB-коллизии
- [ ] Передавать массивы коллизий через `std::span`
- [ ] Реализовать `EventBus` с type erasure для событий
- [ ] Отправлять событие `CollisionEvent` при пересечении
- [ ] Обрабатывать урон: уменьшать `Health`, уничтожать при HP <= 0
- [ ] Пометить горячие системы `final` для помощи девиртуализации
- [ ] Перевести `Transform` storage на SoA (отдельные vector для x, y, rot)

## Фаза 5 — Частицы и Object Pool

- [ ] Определить struct `Particle` (позиция, скорость, lifetime, color, alpha)
- [ ] Реализовать `ObjectPool<Particle, N>` на `std::array<std::byte, N * sizeof(Particle)>`
- [ ] Использовать placement new при `acquire()` и явный деструктор при `release()`
- [ ] Реализовать `ParticleSystem` с обновлением и отрисовкой активных частиц
- [ ] Добавить эмиттер двигателя игрока (N частиц/сек)
- [ ] Добавить эмиттер взрыва при уничтожении врага
- [ ] Создать `constexpr` LUT sin/cos на 360 градусов
- [ ] Вызывать `reserve()` на векторах частиц и сущностей
- [ ] Написать Google Benchmark: ObjectPool vs `vector<Particle>` с new/delete
- [ ] Написать Google Benchmark: SoA vs AoS для 500 Transform

## Фаза 6 — Волны, апгрейды, UI

- [ ] Создать `assets/waves.json` с описанием волн (тип врага, количество, задержка)
- [ ] Реализовать `WaveManager`: спавн врагов по таймеру из JSON
- [ ] Парсить волны с structured bindings: `auto [type, count, delay] = ...`
- [ ] Реализовать счётчик обломков (scrap) при уничтожении врагов
- [ ] Реализовать экран апгрейда между волнами
- [ ] Определить `std::variant<SpeedBoost, ShieldUpgrade, FireRateUpgrade>`
- [ ] Применять апгрейд к игроку через `std::visit`
- [ ] Реализовать HUD: полоска HP, счёт, номер волны
- [ ] Реализовать экран Game Over с итоговым счётом
- [ ] Реализовать главное меню (Start / Quit)
- [ ] Использовать fold expression для суммирования урона за волну
- [ ] Использовать ranges/views для подсчёта живых врагов

## Фаза 7 — Асинхронность

- [ ] Создать thread-safe очередь задач загрузки (`std::queue` + `std::mutex`)
- [ ] Запустить `std::jthread` для фоновой загрузки ассетов следующей волны
- [ ] Использовать `std::condition_variable` для уведомления о завершении загрузки
- [ ] Защитить очередь через `std::scoped_lock`
- [ ] Передавать владение загруженными ресурсами через `std::unique_ptr`
- [ ] Добавить `std::atomic<bool>` флаг `loading_complete`
- [ ] Показать индикатор загрузки в UI между волнами
- [ ] Реализовать procedural wave generator как C++20 coroutine с `co_yield`
- [ ] Использовать `std::async` для генерации spatial grid в фоне (эксперимент)
- [ ] Применить `std::execution::par` к сортировке сущностей по глубине (Y-sort)
- [ ] Прогнать Thread Sanitizer и убедиться в отсутствии data races

## Фаза 8 — Сохранения и сериализация

- [ ] Определить struct `SaveData` (high score, разблокированные апгрейды, настройки)
- [ ] Реализовать сохранение в `saves/profile.json` через `std::filesystem`
- [ ] Реализовать загрузку с `std::optional<SaveData>` при отсутствии файла
- [ ] Написать variadic template `serialize(std::ostream&, Fields&&...)` с fold expressions
- [ ] Использовать `if constexpr` для ветвления по типу поля при сериализации
- [ ] Использовать type traits (`std::is_arithmetic_v`) для выбора формата
- [ ] Добавить `static_assert` на размер и layout критичных структур
- [ ] Логировать события через `std::format` (C++20)
- [ ] Загружать настройки (громкость, fullscreen) при старте приложения
- [ ] Написать unit-тест: round-trip save → load сохраняет данные

## Фаза 9 — Полировка и инженерная культура

- [ ] Написать тесты Catch2 для `SpatialHash` (вставка, запрос, удаление)
- [ ] Написать тесты Catch2 для `ObjectPool` (acquire, release, exhaustion)
- [ ] Написать тесты Catch2 для парсера `waves.json`
- [ ] Написать тесты Catch2 для `EventBus` (подписка, отписка, доставка)
- [ ] Добавить CI-скрипт: configure, build, test
- [ ] Прогнать AddressSanitizer на полном игровом сеансе
- [ ] Прогнать UndefinedBehaviorSanitizer
- [ ] Минимизировать include-зависимости через forward declaration
- [ ] Применить PIMPL к `AudioEngine` (если ещё не сделано)
- [ ] Опционально: вынести модуль `core.entity` в C++20 modules
- [ ] Опционально: policy-based `SparseSet` storage как альтернатива `ComponentArray`
- [ ] Провести профилирование горячего кадра и устранить очевидные узкие места
- [ ] Обновить README и ROADMAP по итогам проекта

## MVP — минимально играбельная версия

- [ ] MVP: RAII-обёртки + окно + спрайт игрока
- [ ] MVP: движение WASD
- [ ] MVP: 5 врагов-преследователей (ChaserAI)
- [ ] MVP: AABB-коллизии + HP
- [ ] MVP: 100 частиц взрыва через object pool
- [ ] MVP: счёт и экран Game Over
