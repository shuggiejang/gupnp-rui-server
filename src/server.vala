errordomain RUIError {
    BAD_CONFIG
}

struct RemoteUI {
    public RemoteUI(string id, string name, string? description, string url)
    {
        this.id = id;
        this.name = name;
        this.description = description;
        this.url = url;
    }
    string id;
    string name;
    string? description;
    string url;
}

class RemoteUIServer {
    static const string REMOTE_UI_SERVICE_TYPE = "urn:schemas-upnp-org:service:RemoteUIServer:1";

    string root_device_xml;
    string service_directory;

    GUPnP.Context context;
    GUPnP.RootDevice root_device;
    
    static RemoteUI[] remoteUIs = {
        RemoteUI("767cc58a-47d2-4fb3-b27e-f6c0d54f26b6", "CableLabs Remote UI Discovery Server", null, "http://10.43.0.93:8080")
    };

    public RemoteUIServer(string root_device_xml, string service_directory) {
        this.root_device_xml = root_device_xml;
        this.service_directory = service_directory;
    }

    public void start() throws Error {
        context = new GUPnP.Context(null, null, 0);
        root_device = new GUPnP.RootDevice(context, root_device_xml,
            service_directory);
        root_device.set_available(true);
        stdout.printf("Running UPnP service on http://%s:%u/%s\n", context.host_ip, context.port, root_device.description_path);

        var service = (GUPnP.Service)root_device.get_service(REMOTE_UI_SERVICE_TYPE);
        if (service == null) {
            throw new RUIError.BAD_CONFIG(
                "Unable to get %s.".printf(REMOTE_UI_SERVICE_TYPE));
        }
        service.action_invoked["GetCompatibleUIs"].connect(on_get_compatible_uis);
        
        MainLoop loop = new MainLoop();
        Unix.signal_add(Posix.SIGINT, () => {
            loop.quit();
            return true;
        });
        loop.run();
        root_device.set_available(false);
    }
    
    void on_get_compatible_uis(GUPnP.ServiceAction action) {
        StringBuilder builder = new StringBuilder("<uilist>");
        foreach (RemoteUI ui in remoteUIs) {
            builder.append("<ui>");
            builder.append("<uiID>");
            builder.append(ui.id);
            builder.append("</uiID>");
            builder.append("<name>");
            builder.append(ui.name);
            builder.append("</name>");
            if (ui.description != null) {
                builder.append("<description>");
                builder.append(ui.description);
                builder.append("</description>");
            }
            builder.append("<protocol shortName=\"DLNA-HTML5-1.0\"><uri>");
            builder.append(ui.url);
            builder.append("</uri></protocol>");
            builder.append("</ui>");
        }
        builder.append("</uilist>");
        action.set_value("UIListing", builder.str);
        action.return();
    }
}

static string? config_file = null;
static bool debug = false;

static const OptionEntry[] options = {
    { "config-file", 'c', 0, OptionArg.FILENAME, ref config_file,
        "The server config file. See config/config.json for an example.",
        "[file]" },
    { "debug", 'd', 0, OptionArg.NONE, ref debug,
        "Print debug messages to the console", null },
    { null }
};

static int main(string[] args) {
    string? root_device_xml;
    string? service_directory;
    try {
        var opt_context = new OptionContext("UPnP RemoteUIServer");
        opt_context.set_help_enabled (true);
        opt_context.add_main_entries (options, null);
        opt_context.parse (ref args);
        if (config_file == null) {
            throw new OptionError.BAD_VALUE("Missing --config-file");
        }
    } catch (OptionError e) {
        stderr.printf ("%s\n", e.message);
        stderr.printf ("Run '%s --help' to see a full list of available command line options.\n",
            args[0]);
        return 2;
    }
    try {
        var parser = new Json.Parser();
        parser.load_from_file(config_file);

        var root = parser.get_root();
        var object = root.get_object();
        root_device_xml = object.get_string_member("root-device-xml");
        if (root_device_xml == null) {
            throw new RUIError.BAD_CONFIG("Missing \"root-device-xml\"");
        }
        service_directory = object.get_string_member("service-directory");
        if (service_directory == null) {
            throw new RUIError.BAD_CONFIG("Missing \"service-directory\"");
        }
        if (!Path.is_absolute(service_directory)) {
            service_directory = Path.build_filename(Path.get_dirname(config_file), service_directory);
        }
    } catch (Error e) {
        stderr.printf("Error reading config file %s.\n", config_file);
        return 3;
    }
    try {
        RemoteUIServer server = new RemoteUIServer(root_device_xml,
            service_directory);
        server.start();
        return 0;
    } catch (Error e) {
        stderr.printf("Error running RemoteUIServer: %s\n", e.message);
        return 1;
    }
}
