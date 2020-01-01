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
    "cmd": "ON",
    "someArg": 123,
    "more": "even more args"
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


The **customer** asks the **endpoint** to turn the **preheating** on. The endpoint verifies the customers pin with the current **configuration** and, if the pin matches, sends the "on" command to the preheating interface. The endpoint then **answer**s the customer with the result of the command or an error.

```c++
Customer customer;
Preheating preheating;
Configuration config("1234");
Endpoint endpoint(config, preheating);
Answer<T> answer = endpoint.turnOnPreheating(pin);

assertNotNull(answer);
assertFalse(answer.isError());




// Answer#isError() => bool
// Answer#message() => string
// Answer#payload() => T
// Answer implements JsonMessageHandler, StringMessageHandler
// Answer#jsonMessage() => JsonDocument; Answer#stringMessage() => std::string



class OnTextHandlerFactory implements HandlerFactory {
    TextRequestParser parser;
    Endpoint endpoint;

    boolean supports(std::string rawRequest) {
        return parser.canRead(rawRequest) && parser.parse(rawRequest).command() == "ON";
    }
    
    Handler forRequest(std::string rawRequest) {
        auto request = parser.parse(rawRequest);
        return OnTextHandler(endpoint, request);
    }
}

class OnTextHandler {
    Endpoint endpoint;
    TextRequest request;

    OnTextHandler(Endpoint endpoint, TextRequest request) {
    }

    boolean supports() {
        return request.isParsedSuccessfully() && "ON" == request.command();
    }

    Response execute() {
        auto answer = endpoint.turnOnPreheating(request.pin());
        return Response.success(answer.stringMessage()).empty();
    }
}





HanlderFactory[] factories = {
    OnTextHandler(...),
    OnJsonHandler(...)
};

std::string rawRequest = "...";

factories.map([rawRequest](factory) { return factory.forRequest(rawRequest); });
for (auto factory : factories) {
    factory.forRequest()
}



RawRequest req = receive();
RawResponse res = to_raw_response(req);
send(res);



RawResponse to_raw_response(const RawRequest &req) {
    ParsedRequest *parsedRequest;
    if (req.ContentType() == "application/json") {
        //JsonDocument doc = JsonLib::parse_json(req.Content());
        ParsedJsonRequest jsonRequest = JsonRequestParser.Parse(req.Content());


    } else if (req.ContentType() == "text/plain") {
        ParsedTextRequest textRequest = TextRequestParser.Parse(req.Content());

    } else {
        return UnknownRequestResponse{};
    }
    
}



Extract

```

```c
std::string rawRequest = "something";

auto handler = findHandler(rawRequest);
if (handler == NULL) {
    return;
}
//auto request = handler.extractRequest();
auto request = handler.parse(rawRequest);
auto response = request.execute();

//response.send();
sendResponse(response);









handlers
  .filter(x => x.supports(rawRequest))
  .map(x => x.setupHandler(rawRequest))
  .findFirst()
  .orElse(null);





class Handler {
    Request parse(std::string rawRequest) {
        
    }
}

class Request {
    Response execute() {

    }
}




```




```c
std::string rawRequest = "something";

auto parser = findParser(rawRequest);
if (parser == NULL) {
    return;
}
auto request = parser.parse(rawRequest);

controller = findController(request);

auto response = controller.execute(request);

//response.send();
sendResponse(response);


```

