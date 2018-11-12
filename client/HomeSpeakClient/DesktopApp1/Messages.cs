using System;
using System.Collections.Generic;

public class Messages
{
    private List<ReadedMessage> data = new List<ReadedMessage>();

    public List<ReadedMessage> Data { get => data; set => data = value; }
}
