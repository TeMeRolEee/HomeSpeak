using System;

public class MessageCollection
{
    private List<Message> Messages;

    public List<Message> Messages1 { get => Messages; set => Messages = value; }
    public void Deserialize(string serializ)
    {
        Messages Mes = new System.Web.Script.Serialization.JavaScriptSerializer().Deserialize<Messages>(json);
    }
}
