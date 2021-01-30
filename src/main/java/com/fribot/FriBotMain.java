package com.fribot;

import discord4j.core.*;
import discord4j.core.event.domain.lifecycle.ReadyEvent;
import discord4j.core.object.entity.User;


/**
* Hello world!
*
*/

public class FriBotMain
{
    public static GatewayDiscordClient getClient()
    {
        GatewayDiscordClient client; 
        
        client = DiscordClientBuilder.create("ODA1MDM2NDUxNDY1MTM0MTAw.YBVCng.jRcRFdCYsO2UiCQKnEXep13mMMQ")
        .build()
        .login()
        .block();

        return client;
    }
    public static void main( String[] args )
    {

        FriBotMsgEvents msgEvents = new FriBotMsgEvents();
        
        getClient().getEventDispatcher().on(ReadyEvent.class)
            .subscribe(event -> {
            final User self = event.getSelf();
            System.out.println(String.format(
                "Logged in as %s#%s", self.getUsername(), self.getDiscriminator()
            ));
            });

        msgEvents.chatMsgEvent();
        msgEvents.kerem();
        
        getClient().onDisconnect().block();
    }
}
