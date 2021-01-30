package com.fribot;

import discord4j.core.event.domain.message.MessageCreateEvent;
import discord4j.core.object.entity.Message;

/**
 * A simple Java class!
 */
public class FriBotMsgEvents
{
    // Properties

    int keremCounter = 0;
    
    // Constructors
    
    // Methods

    public void chatMsgEvent()
    {
        FriBotMain.getClient().getEventDispatcher().on(MessageCreateEvent.class)
        .map(MessageCreateEvent::getMessage)
        .filter(message -> message.getAuthor().map(user -> !user.isBot()).orElse(false))
        .filter(message -> message.getContent().equalsIgnoreCase("fb?deneme"))
        .flatMap(Message::getChannel)
        .flatMap(channel -> channel.createMessage("test"))
        .subscribe();
    }

    public void kerem()
    {
        FriBotMain.getClient().getEventDispatcher().on(MessageCreateEvent.class)
        .map(MessageCreateEvent::getMessage)
        .filter(message -> message.getAuthor().map(user -> user.getId()
                                                               .asString()
                                                               .equals(KEREM_ID))
                                                               .orElse(false)) // isBot check is redundant since the ID is known
        .filter(message -> {
            keremCounter++;
            return keremCounter % 5 == 0; // Send on every 5 messages

        }) // Stupid "filter"
        .flatMap(Message::getChannel)
        .flatMap(channel -> channel.createMessage("test"))
        .subscribe();
    }
    
}
