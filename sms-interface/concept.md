# Ideas

- Structured format for communication with machines (e.g. Android app) => json
- Simple format for communication with humans (e.g. setup, fallback) => text

## Communication

- Every sent message must contain a pin to authenticate the request
- Any message that cannot authenticate itself is just ignored. There will be
  no answer. This will prevent the interface from answering junk texts and
  maybe wasting money.

## Which commands?

Needed:
- ON / OFF obviously
- SETPIN to setup or change the pin

Maybe:
- STATUS (active or not, configured running time, hot or cold, etc.)


# Simple text format

```
Format: <identifier> <pin> <command>

PHC 4711 ON
=> The preheating is active now.
=> <no answer> if the pin isn't correct
=> Could not activate the preheating because the battery is low.
=> Could not reach the car.


PHC 4711 SETPIN 1337
=> The pin was changed successfully.
=> <no answer> if the pin isn't correct

PHC 1337 OFF
=> The preheating is inactive now.
=> <no answer> if the pin isn't correct
```

# JSON format

- Even if it's json, we shoud keep the format compact, because texts are so
  limited in length (more length = higher cost)
- As the goal of this is better machine readability, we should answer in 
  machine-friendly enum values, too. The translation to a real message can
  be made in each client individually.

```json
{
    "pin": "4711",
    "cmd": "ON"
}
```

```json
{
    "pin": "4711",
    "cmd": {
        "nme": "ON",
        "ags": []
    }
}
```