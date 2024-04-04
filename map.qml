import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    id: window
    width: 800
    height: 600

    signal locationPicked(double lat, double lng)
    signal updateLineEdit(double lat, double lng)

    property double oldLat: 25.6585
    property double oldLng: 100.3658
    property Component comMarker: mapMarker
    property bool mapReady: false

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: mapView
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(oldLat, oldLng);
        zoomLevel: 6
        visible: mapReady

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var coord = mapView.toCoordinate(Qt.point(mouse.x, mouse.y))
                window.locationPicked(coord.latitude, coord.longitude)
                console.log("Picked Location: " + coord.latitude + ", " + coord.longitude)
                window.updateLineEdit(coord.latitude, coord.longitude); // Emit signal to update line edit
            }
        }
    }

    Component.onCompleted: {
        mapReady = true;
        // Center the map on Tunisia when it's completed loading
        setCenter(34.0479, 9.9183);
        // Coordinates for Tunisia (latitude, longitude)
    }

    function setCenter(lat, lng) {
        mapView.center = QtPositioning.coordinate(lat, lng);
        oldLat = lat
        oldLng = lng
    }

    function addMarker(lat, lng) {
        var item = comMarker.createObject(window, {
                                           coordinate: QtPositioning.coordinate(lat, lng)
                                          })
        mapView.addMapItem(item)
    }

    Component {
        id: mapMarker
        MapQuickItem {
            id: markerImg
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: position

            sourceItem: Image {
                id: image
                source: "http://maps.gstatic.com/mapfiles/ridefinder-images/mm_20_red.png"
            }
        }
    }

    Connections {
        target: window
        onLocationPicked: {
            // Update the title with the picked location
            Qt.application.title = "Picked Location: " + lat + ", " + lng
            // Add a marker to the picked location on the map
            addMarker(lat, lng)
        }
    }
}
