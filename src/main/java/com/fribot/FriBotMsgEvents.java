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
        .filter(message -> message.getAuthor().map(user -> !user.isBot()).orElse(false))
        .filter(message -> message.getAuthor().map(user -> { keremCounter = keremCounter + 1; return user.getId().asString().equals( "198374148852940800"); }).orElse(false) )
        .flatMap(Message::getChannel)
        .flatMap(channel -> channel.createMessage("test"))
        .subscribe();
    }
    
}